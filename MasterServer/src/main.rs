use actix_cors::Cors;
use async_recursion::async_recursion;
use core::fmt;
use std::collections::BTreeMap;

use actix_web::{get, web, App, HttpResponse, HttpServer, Responder, Result as ActixResult};
use rand::Rng;
use serde::{Deserialize, Serialize};
use serde_json::json;

type Petal = (u64, u64, i64);

type Result<T> = std::result::Result<T, Error>;

const DIRECTORY_SECRET: &str = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const CLOUD_TOKEN: &str = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID: &str = "04cfba67-e965-4899-bcb9-b7497cc6863b";
const SERVER_SECRET: &str = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";

#[derive(Debug)]
pub enum Error {
    InvalidPetalEntry,
    InvalidIdFormat,
    InvalidRarityFormat,
    InvalidCountFormat,
    InvalidPassword,
    InvalidJson,
    InvalidReqwest,
    InvalidReqwestResponse,
    InvalidPetalsFormat,
    InsufficientFunds,
    AccountAlreadyExists,
    AccountDoesNotExist,
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Error::InvalidPetalEntry => write!(f, "InvalidPetalEntry"),
            Error::InvalidIdFormat => write!(f, "InvalidIdFormat"),
            Error::InvalidRarityFormat => write!(f, "InvalidRarityFormat"),
            Error::InvalidCountFormat => write!(f, "InvalidCountFormat"),
            Error::InvalidPassword => write!(f, "InvalidPassword"),
            Error::InvalidJson => write!(f, "InvalidJson"),
            Error::InvalidReqwest => write!(f, "InvalidReqwest"),
            Error::InvalidReqwestResponse => write!(f, "InvalidReqwestResponse"),
            Error::InvalidPetalsFormat => write!(f, "InvalidPetalsFormat"),
            Error::InsufficientFunds => write!(f, "InsufficientFunds"),
            Error::AccountAlreadyExists => write!(f, "AccountAlreadyExists"),
            Error::AccountDoesNotExist => write!(f, "AccountDoesNotExist"),
        }
    }
}

fn rivet_url(key: &str) -> String {
    format!(
        "https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}&key={}",
        key
    )
}

fn get_craft_chance(rarity: u64) -> f32 {
    match rarity {
        0 => 0.5,  // common -> uncommon
        1 => 0.3,  // uncommon -> rare
        2 => 0.15, //rare -> epic
        3 => 0.05, // epic -> legendary
        4 => 0.03, // legendary -> mythic
        5 => 0.01, // mythic -> ultra
        _ => 0.0,  // aka nothing
    }
}

fn craft(count: i64, chance: f32) -> (i64, i64) {
    if chance == 0.0 {
        return (count, 0);
    }
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

async fn make_request(
    url: &str,
    method: reqwest::Method,
    body: Option<String>,
) -> Result<serde_json::Value> {
    match &body {
        Some(x) => println!("{} /{}\n{}", url, method.to_string(), x.clone()),
        None => println!("{} /{}\nno body", url, method.to_string()),
    };
    let client = reqwest::Client::new();
    let mut request = client
        .request(method, url)
        .header("Authorization", format!("Bearer {CLOUD_TOKEN}"));

    if let Some(body) = body {
        request = request.body(body);
    }

    let response = request.send().await.map_err(|_| Error::InvalidReqwest)?;
    let text = response
        .text()
        .await
        .map_err(|_| Error::InvalidReqwestResponse)?;
    let value: serde_json::Value = serde_json::from_str(&text).map_err(|_| Error::InvalidJson)?;

    Ok(value)
}

#[derive(Serialize, Deserialize, Debug, Clone)]
struct DatabaseAccount {
    pub password: String,
    pub username: String,
    pub petals: serde_json::Value,
}

#[async_recursion]
async fn user_get(username: &String, password: &String) -> Result<DatabaseAccount> {
    let url = rivet_url(&format!("{}/game/players/{}", DIRECTORY_SECRET, username));
    let a = make_request(&url, reqwest::Method::GET, None).await?;

    if a["value"].is_null() {
        if password == SERVER_SECRET {
            return Err(Error::AccountDoesNotExist);
        }
        user_create(username, password, false).await?;
        return user_get(username, password).await;
    }

    let b: DatabaseAccount =
        serde_json::from_str(&a["value"].to_string()).map_err(|_| Error::InvalidJson)?;

    println!("{} {}", b.password, SERVER_SECRET);

    if password != SERVER_SECRET && b.password != password.as_str() {
        return Err(Error::InvalidPassword);
    }
    Ok(b)
}

async fn user_exists(username: &String) -> Result<bool> {
    let data = make_request(
        &format!("{}/game/players/{}", DIRECTORY_SECRET, username),
        reqwest::Method::GET,
        None,
    )
    .await?;

    Ok(data["value"].is_object())
}

async fn user_create(username: &String, password: &String, safe: bool) -> Result<()> {
    if safe && user_exists(username).await? {
        return Err(Error::AccountAlreadyExists);
    }
    let url = rivet_url(NAMESPACE_ID);
    let account = DatabaseAccount {
        username: username.to_string(),
        password: password.to_string(),
        petals: json!({
            "1:0": 5
        }),
    };
    let request_json = serde_json::json!({
        "key": format!("{}/game/players/{}", DIRECTORY_SECRET, username),
        "namespace_id": NAMESPACE_ID,
        "value": account
    });
    make_request(
        &url,
        reqwest::Method::PUT,
        Some(serde_json::to_string(&request_json).map_err(|_| Error::InvalidJson)?),
    )
    .await?;
    Ok(())
}

async fn user_merge_petals(username: &String, petals: &Vec<Petal>) -> Result<()> {
    let mut user: DatabaseAccount = user_get(username, &SERVER_SECRET.to_string()).await?;

    let mut game_amounts: BTreeMap<String, serde_json::Value> =
        serde_json::from_value(user.petals).map_err(|_| Error::InvalidPetalsFormat)?;

    for petal in petals {
        let key = format!("{}:{}", petal.0, petal.1);
        let count = petal.2;
        let entry = game_amounts
            .entry(key)
            .or_insert_with(|| serde_json::Value::Number(0.into()));

        if let Some(value) = entry.as_i64() {
            *entry = serde_json::Value::Number((value + count).into());
        } else {
            return Err(Error::InvalidCountFormat);
        }
    }

    user.petals = serde_json::to_value(&game_amounts).map_err(|_| Error::InvalidJson)?;

    let url = rivet_url(NAMESPACE_ID);
    let request_json = serde_json::json!({
        "key":serde_json::value::to_value(format!("{}/game/players/{}", DIRECTORY_SECRET, username)).unwrap(),
        "namespace_id": NAMESPACE_ID.to_string(),
        "value": user
    });
    make_request(
        &url,
        reqwest::Method::PUT,
        Some(serde_json::to_string(&request_json).map_err(|_| Error::InvalidJson)?),
    )
    .await?;

    Ok(())
}

async fn user_craft_petals(
    username: &String,
    password: &String,
    petals: &mut Vec<Petal>,
) -> Result<String> {
    // Check if each petal has enough quantity
    for petal in petals.iter() {
        if petal.2 < 5 {
            return Err(Error::InsufficientFunds);
        }
    }

    let user: DatabaseAccount = user_get(username, password).await?;

    let mut game_amounts: BTreeMap<String, serde_json::Value> =
        serde_json::from_value(user.petals).map_err(|_| Error::InvalidPetalsFormat)?;

    // assert valid
    for petal in petals.iter() {
        let key = format!("{}:{}", petal.0, petal.1);
        let count = petal.2;

        let entry = game_amounts
            .entry(key)
            .or_insert_with(|| serde_json::Value::Number(0.into()));

        match entry.as_i64() {
            Some(x) => {
                if x < count {
                    return Err(Error::InsufficientFunds);
                }
            }
            None => return Err(Error::InvalidCountFormat),
        };
    }

    // craft
    let mut craft_results = Vec::with_capacity(petals.len());

    for petal in petals.iter() {
        let (id, rarity) = (petal.0, petal.1);
        let count = petal.2;

        let (petals_left, new_petals) = craft(count, get_craft_chance(rarity));
        craft_results.push((id, rarity + 1, new_petals));
        craft_results.push((id, rarity, petals_left - count));
    }

    // merge
    user_merge_petals(username, &craft_results).await?;

    // create a vector of strings where each string is formatted as "id:rarity:count"
    let results: Vec<String> = craft_results
        .iter()
        .map(|result| format!("{}:{}:{}", result.0, result.1, result.2))
        .collect();

    // join the results with commas and return the result
    Ok(results.join(","))
}

fn parse_petals_string(petals_string: &str) -> Result<Vec<Petal>> {
    let mut petals = vec![];
    for entry in petals_string.split(",") {
        let parts: Vec<&str> = entry.split(":").collect();
        if parts.len() != 3 {
            return Err(Error::InvalidPetalEntry);
        }

        let id: u64 = parts[0].parse().map_err(|_| Error::InvalidIdFormat)?;
        let rarity: u64 = parts[1].parse().map_err(|_| Error::InvalidRarityFormat)?;
        let count: i64 = parts[2].parse().map_err(|_| Error::InvalidCountFormat)?;

        petals.push((id, rarity, count));
    }
    Ok(petals)
}

#[get("/user_get/{username}/{password}")]
async fn user_get_req(uri: web::Path<(String, String)>) -> ActixResult<impl Responder> {
    match user_get(&uri.0, &uri.1).await {
        Ok(r) => Ok(HttpResponse::Ok().body(serde_json::to_string(&r).unwrap())),
        Err(x) => Ok(HttpResponse::BadRequest().body(x.to_string())),
    }
}

#[get("/user_create/{username}/{password}")]
async fn user_create_req(uri: web::Path<(String, String)>) -> ActixResult<impl Responder> {
    match user_create(&uri.0, &uri.1, true).await {
        Ok(_) => Ok(HttpResponse::Ok().body("success")),
        Err(x) => Ok(HttpResponse::BadRequest().body(x.to_string())),
    }
}

#[get("/user_exists/{username}")]
async fn user_exists_req(uri: web::Path<String>) -> ActixResult<impl Responder> {
    match user_exists(&uri.to_string()).await {
        Ok(x) => Ok(HttpResponse::BadRequest().body(if x { "1" } else { "0" })),
        Err(x) => Ok(HttpResponse::BadRequest().body(x.to_string())),
    }
}

#[get("user_merge_petals/{server_secret}/{username}/{petals_string}")]
async fn user_merge_petals_req(
    uri: web::Path<(String, String, String)>,
) -> ActixResult<impl Responder> {
    if uri.0 != SERVER_SECRET {
        return Ok(HttpResponse::BadRequest().body("Invalid server auth"));
    };
    let petals = match parse_petals_string(&uri.2.to_string()) {
        Ok(x) => x,
        Err(x) => return Ok(HttpResponse::BadRequest().body(x.to_string())),
    };
    match user_merge_petals(&uri.1.to_string(), &petals).await {
        Ok(_) => Ok(HttpResponse::Ok().body("success")),
        Err(x) => Ok(HttpResponse::BadRequest().body(x.to_string())),
    }
}

#[get("user_craft_petals/{username}/{password}/{petals_string}")]
async fn user_craft_petals_req(
    uri: web::Path<(String, String, String)>,
) -> ActixResult<impl Responder> {
    let mut petals = match parse_petals_string(&uri.2.to_string()) {
        Ok(x) => x,
        Err(x) => return Ok(HttpResponse::BadRequest().body(x.to_string())),
    };
    match user_craft_petals(&uri.0.to_string(), &uri.1.to_string(), &mut petals).await {
        Ok(x) => Ok(HttpResponse::Ok().body(x)),
        Err(x) => Ok(HttpResponse::BadRequest().body(x.to_string())),
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .wrap(
                Cors::default()
                    .allow_any_origin()
                    .allow_any_header()
                    .allow_any_method(),
            )
            .service(
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
