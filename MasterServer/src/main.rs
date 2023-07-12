use actix_web::{get, web, App, HttpResponse, HttpServer, Responder};
use serde::{Deserialize, Serialize};
use serde_json::Map;
/*
a = await fetch("https://kv.api.rivet.gg/v1/entries", {
    headers: {
        Authorization: "Bearer cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA"
    },
    method: "PUT",
    body: '{"key":"a92pd3nf29d38tny9pr34dn3d908ntgb/game/players/example/petals/15:1","namespace_id":"04cfba67-e965-4899-bcb9-b7497cc6863b","value":123456789012345678901}'
})
b = await a.json()




a = await fetch("https://kv.api.rivet.gg/v1/entries?key=a92pd3nf29d38tny9pr34dn3d908ntgb/game/players/example/petals/15:1&namespace_id=04cfba67-e965-4899-bcb9-b7497cc6863b", {
    headers: {
        Authorization: "Bearer cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA"
    },
})
b = await a.json()
*/

const DIRECTORY_SECRET: &str = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const CLOUD_TOKEN: &str = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID: &str = "04cfba67-e965-4899-bcb9-b7497cc6863b"; // prod
                                                                   // const PETAL_COUNT: u64 = 11;
                                                                   // const RARITY_COUNT: u64 = 8;

#[derive(Serialize, Deserialize, Debug, Clone)]
struct DatabaseAccount {
    pub password: String,
    pub username: String,
    pub petals: serde_json::Value,
}

async fn get_user(username: &String, password: &String) -> Result<String, String> {
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
    if a["value"].is_null() {
        if a["watch"].is_null() {
            return Err("invalid username".to_string());
        }
        return Err(format!(
            "{{\"error\":\"not a rivet account?\",\"rivet_response\":{}}}",
            a.to_string()
        )
        .to_string());
    }

    let b: DatabaseAccount = serde_json::from_str(&a["value"].to_string()).unwrap();

    if b.password != password.as_str() {
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
    if safe {
        if user_exists(username).await? {
            return Err("account already exists".to_string());
        }
    }
    let url = format!("https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}");
    let r = reqwest::Client::new()
        .put(url)
        .body({
            let account = DatabaseAccount {
                username: username.to_string(),
                password: password.to_string(),
                petals: serde_json::Value::Object(Map::new()),
            };
            let mut request_values = Map::new();
            request_values.insert("key".to_string(), serde_json::value::to_value(format!("{DIRECTORY_SECRET}/game/players/{username}")).unwrap());
            request_values.insert("namespace_id".to_string(), serde_json::value::to_value(NAMESPACE_ID.to_string()).unwrap());
            request_values.insert("value".to_string(), serde_json::value::to_value(account).unwrap());
            let request_json = serde_json::Value::Object(request_values);
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

#[get("/get_user/{username}/{password}")]
async fn get_user_req(uri: web::Path<(String, String)>) -> impl Responder {
    match get_user(&uri.0, &uri.1).await {
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

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new().service(
            web::scope("/api")
                .service(get_user_req)
                .service(user_create_req)
                .service(user_exists_req)
        )
    })
    .workers(10)
    .bind(("127.0.0.1", 55554))?
    .run()
    .await
}
