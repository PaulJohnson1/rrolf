use actix_web::{get, web, App, HttpResponse, HttpServer, Responder};
use reqwest::StatusCode;
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

struct DatabaseAccount {
    pub password: String,
    pub username: String,
    pub petals: serde_json::Value,
}

async fn maybe_create_account(username: &String, password: &String) -> Result<String, String> {
    Ok("aa".to_string())
}

async fn get_user_impl(username: &String, password: &String) -> Result<String, String> {
    maybe_create_account(&username, &password).await?;

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
    let b = &a["value"];
    if b.is_null() {
        if a["watch"].is_null() {
            return Err("invalid username".to_string());
        }
        return Err(format!("{{\"error\":\"not a rivet account?\",\"rivet_response\":{}}}", a.to_string()).to_string());
    }

    if b["password"].as_str().expect("password doesn't exist") != password.as_str() {
        return Err("invalid password".to_string());
    }
    Ok(b.to_string())
}

#[get("/get_user/{username}/{password}")]
async fn get_user(uri: web::Path<(String, String)>) -> impl Responder {
    println!("getting user {} {}", uri.0, uri.1);
    match get_user_impl(&uri.0, &uri.1).await {
        Ok(r) => HttpResponse::Ok().body(r),
        Err(r) => HttpResponse::BadRequest().body(r),
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| App::new().service(get_user))
        .bind(("127.0.0.1", 55554))?
        .run()
        .await
}
