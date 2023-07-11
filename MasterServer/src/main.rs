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

async fn maybe_create_account(username: &String, auth: &String) -> Result<String, String> {
    Ok("aa".to_string())
}

async fn get_petals_impl(username: &String, auth: &String) -> Result<String, String> {
    maybe_create_account(&username, &auth).await?;

    let url = format!("https://kv.api.rivet.gg/v1/entries?namespace_id={NAMESPACE_ID}&key={DIRECTORY_SECRET}/game/players/{username}/petals");

    let a = reqwest::Client::new();
    let a = a.get(url);
    let a = a.header("Authorization", format!("Bearer {CLOUD_TOKEN}"));
    let a = a.send();
    let a = a.await;

    if let Err(_) = a {
        return Err("internal1".to_string());
    }
    let a = a.unwrap();
    let a = a.text().await;
    if let Err(_) = a {
        return Err("internal2".to_string());
    }
    let a = a.unwrap();

    let a: serde_json::Value = serde_json::from_str(&a).expect("rivet server json valid");
    let b = &a["value"];
    if b.is_null() {
        return Ok(a.to_string());
    }
    Ok(b.to_string())
}

#[get("/get_petals/{username}/{password}")]
async fn get_petals(uri: web::Path<(String, String)>) -> impl Responder {
    match get_petals_impl(&uri.0, &uri.1).await {
        Ok(r) => HttpResponse::Ok().body(r),
        Err(_) => HttpResponse::BadRequest().finish(),
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| App::new().service(get_petals))
        .bind(("127.0.0.1", 55554))?
        .run()
        .await
}
