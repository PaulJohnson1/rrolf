use std::collections::BTreeMap;

use actix_web::{get, web, App, HttpResponse, HttpServer, Responder};
use rand::Rng;
use serde::{Deserialize, Serialize};
use serde_json::Map;

const DIRECTORY_SECRET: &str = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const CLOUD_TOKEN: &str = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID: &str = "04cfba67-e965-4899-bcb9-b7497cc6863b"; // prod
const SERVER_SECRET: &str = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";

fn craft(count: i64, chance: f32) -> (i64, i64) {
    let mut successes = 0;
    let mut count = count;
    while count >= 5 {
        if ((rand::thread_rng().gen_range(0..2147483647) as f64 / 2147483647.0) as f32) < chance {
            successes += 1;
            count -= 5;
        } else {
            count -= rand::thread_rng().gen_range(1..=4);
        }
    }
    (count, successes)
}

#[derive(Serialize, Deserialize, Debug, Clone)]
struct DatabaseAccount {
    pub password: String,
    pub username: String,
    pub petals: serde_json::Value,
}

async fn user_get(
    username: &String,
    password: &String,
    use_password: bool,
) -> Result<String, String> {
    let url = format!("https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}&key={DIRECTORY_SECRET}/game/players/{username}");
    let response = reqwest::Client::new()
        .get(url)
        .header("Authorization", format!("Bearer {CLOUD_TOKEN}"))
        .send()
        .await
        .map_err(|_| "internal1".to_string())?
        .text()
        .await
        .map_err(|_| "internal2".to_string())?;

    let a: serde_json::Value = serde_json::from_str(&response).expect("rivet server json valid");
    if a["value"].is_null() {
        println!("not a rivet account error: {response}");
        return Err("not a rivet account".to_string());
    }

    let b: DatabaseAccount = serde_json::from_str(&a["value"].to_string()).unwrap();

    if use_password && b.password != password.as_str() {
        return Err("invalid password".to_string());
    }
    Ok(serde_json::to_string(&b).unwrap())
}

async fn user_exists(username: &String) -> Result<bool, String> {
    let url = format!("https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}&key={DIRECTORY_SECRET}/game/players/{username}");
    let a = reqwest::Client::new()
        .get(url)
        .header("Authorization", format!("Bearer {CLOUD_TOKEN}"))
        .send()
        .await
        .map_err(|_| "internal1".to_string())?
        .text()
        .await
        .map_err(|_| "internal2".to_string())?;

    let a: serde_json::Value = serde_json::from_str(&a).expect("rivet server json valid");
    Ok(!a["value"].is_null())
}

async fn user_create(username: &String, password: &String, safe: bool) -> Result<(), String> {
    if safe && user_exists(username).await? {
        return Err("account already exists".to_string());
    }
    let url = format!("https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}");
    reqwest::Client::new()
        .put(url)
        .body({
            let account = DatabaseAccount {
                username: username.to_string(),
                password: password.to_string(),
                petals: serde_json::Value::Object(Map::new()),
            };
            let request_json = serde_json::json!({
                "key":serde_json::value::to_value(format!("{DIRECTORY_SECRET}/game/players/{username}")).unwrap(),
                "namespace_id": NAMESPACE_ID.to_string(),
                "value": account
            });
            serde_json::to_string(&request_json).unwrap()
        })
        .header("Authorization", format!("Bearer {CLOUD_TOKEN}"))
        .send()
        .await
        .map_err(|_| "internal1".to_string())?
        .text()
        .await
        .map_err(|_| "internal2".to_string())?;
    Ok(())
}

async fn user_merge_petals(
    username: &String,
    petals: &Vec<(u64, u64, i64)>,
    safe: bool,
) -> Result<(), String> {
    if safe && !user_exists(username).await? {
        return Err("account does not exist".to_string());
    }

    let mut user: DatabaseAccount =
        serde_json::from_str(&user_get(username, &"".to_string(), false).await?)
            .map_err(|_| "user_get returned invalid json")?;

    let mut game_amounts: BTreeMap<String, serde_json::Value> =
        serde_json::from_value(user.petals).map_err(|_| "Invalid petals format")?;
    for petal in petals {
        let key = format!("{}:{}", petal.0, petal.1);
        let count = petal.2;
        let entry = game_amounts
            .entry(key)
            .or_insert_with(|| serde_json::Value::Number(0.into()));

        if let Some(value) = entry.as_i64() {
            *entry = serde_json::Value::Number((value + count).into());
        } else {
            return Err("Invalid count format".to_string());
        }
    }

    user.petals =
        serde_json::to_value(&game_amounts).map_err(|_| "Failed to serialize game_amounts")?;

    let url = format!("https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}");
    reqwest::Client::new()
        .put(url)
        .body({
            let request_json = serde_json::json!({
                "key":serde_json::value::to_value(format!("{DIRECTORY_SECRET}/game/players/{username}")).unwrap(),
                "namespace_id": NAMESPACE_ID.to_string(),
                "value": user
            });
            serde_json::to_string(&request_json).unwrap()
        })
        .header("Authorization", format!("Bearer {CLOUD_TOKEN}"))
        .send()
        .await
        .map_err(|_| "internal1".to_string())?
        .text()
        .await
        .map_err(|_| "internal2".to_string())?;

    Ok(())
}

async fn user_craft_petals(
    username: &String,
    password: &String,
    petals: &mut Vec<(u64, u64, i64)>,
) -> Result<(), String> {
    let len = petals.len();
    for i in 0..len {
        let petal = petals[i];
        if petal.2 < 5 {
            return Err("must have 5 of the petal type".to_string());
        }
    }

    let mut user: DatabaseAccount =
        serde_json::from_str(&user_get(username, password, true).await?)
            .map_err(|_| "user_get invalid json")?;

    let mut game_amounts: BTreeMap<String, serde_json::Value> =
        serde_json::from_value(user.petals).map_err(|_| "Invalid petals format")?;

    // assert valid
    for i in 0..len {
        let petal = petals[i];
        let key = format!("{}:{}", petal.0, petal.1);
        let count = petal.2;

        let entry = game_amounts
            .entry(key)
            .or_insert_with(|| serde_json::Value::Number(0.into()));

        match entry.as_i64() {
            Some(x) => {
                if x < count {
                    return Err("insufficient funds".to_string());
                }
            }
            None => return Err("error reading entry".to_string()),
        };
    }

    // craft
    let mut craft_results = Vec::with_capacity(len);

    for i in 0..len {
        let petal = petals[i];
        let (id, rarity) = (petal.0, petal.1);
        let count = petal.2;

        let (petals_left, new_petals) = craft(count, 0.5);
        craft_results.push((id, rarity + 1, new_petals));
        craft_results.push((id, rarity, petals_left - count));
    }

    // merge
    user_merge_petals(username, &craft_results, false).await?;

    Ok(())
}

#[get("/user_get/{username}/{password}")]
async fn user_get_req(uri: web::Path<(String, String)>) -> impl Responder {
    match user_get(&uri.0, &uri.1, true).await {
        Ok(r) => HttpResponse::Ok().body(r),
        Err(r) => HttpResponse::BadRequest().body(r),
    }
}

#[get("/user_create/{username}/{password}")]
async fn user_create_req(uri: web::Path<(String, String)>) -> impl Responder {
    match user_create(&uri.0, &uri.1, true).await {
        Ok(_) => HttpResponse::Ok().body("success"),
        Err(r) => HttpResponse::BadRequest().body(r),
    }
}

#[get("/user_exists/{username}")]
async fn user_exists_req(uri: web::Path<String>) -> impl Responder {
    match user_exists(&uri.to_string()).await {
        Ok(r) => HttpResponse::Ok().body(if r { "true" } else { "false" }),
        Err(r) => HttpResponse::BadRequest().body(r),
    }
}

#[get("user_merge_petals/{server_secret}/{username}/{petals_string}")]
async fn user_merge_petals_req(uri: web::Path<(String, String, String)>) -> impl Responder {
    if uri.0 != SERVER_SECRET {
        return HttpResponse::BadRequest().body("Invalid server auth");
    };
    let petals_string = uri.2.to_string();
    let mut merged_petals = vec![];
    for entry in petals_string.split(",") {
        let parts: Vec<&str> = entry.split(":").collect();
        if parts.len() != 3 {
            return HttpResponse::BadRequest().body("Invalid petal entry format");
        }

        let id: u64 = match parts[0].parse() {
            Ok(val) => val,
            Err(_) => return HttpResponse::BadRequest().body("Invalid id format"),
        };

        let rarity: u64 = match parts[1].parse() {
            Ok(val) => val,
            Err(_) => return HttpResponse::BadRequest().body("Invalid rarity format"),
        };

        let count: i64 = match parts[2].parse() {
            Ok(val) => val,
            Err(_) => return HttpResponse::BadRequest().body("Invalid count format"),
        };
        merged_petals.push((id, rarity, count));
    }
    match user_merge_petals(&uri.1.to_string(), &merged_petals, false).await {
        Ok(_) => HttpResponse::Ok().body("success"),
        Err(r) => HttpResponse::BadRequest().body(r),
    }
}

#[get("user_craft_petals/{username}/{password}/{petals_string}")]
async fn user_craft_petals_req(uri: web::Path<(String, String, String)>) -> impl Responder {
    let petals_string = uri.2.to_string();
    let mut merged_petals = vec![];
    for entry in petals_string.split(",") {
        let parts: Vec<&str> = entry.split(":").collect();
        if parts.len() != 3 {
            return HttpResponse::BadRequest().body("Invalid petal entry format");
        }

        let id: u64 = match parts[0].parse() {
            Ok(val) => val,
            Err(_) => return HttpResponse::BadRequest().body("Invalid id format"),
        };

        let rarity: u64 = match parts[1].parse() {
            Ok(val) => val,
            Err(_) => return HttpResponse::BadRequest().body("Invalid rarity format"),
        };

        let count: i64 = match parts[2].parse() {
            Ok(val) => val,
            Err(_) => return HttpResponse::BadRequest().body("Invalid count format"),
        };
        merged_petals.push((id, rarity, count));
    }
    match user_craft_petals(&uri.0.to_string(), &uri.1.to_string(), &mut merged_petals).await {
        Ok(_) => HttpResponse::Ok().body("success"),
        Err(r) => HttpResponse::BadRequest().body(r),
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new().service(
            web::scope("/api")
                .service(user_get_req)
                .service(user_create_req)
                .service(user_exists_req)
                .service(user_merge_petals_req)
                .service(user_craft_petals_req),
        )
    })
    .workers(10)
    .bind(("127.0.0.1", 55554))?
    .run()
    .await
}
