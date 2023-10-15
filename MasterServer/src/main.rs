#[macro_use]
extern crate lazy_static;

use actix::{Actor, StreamHandler};
use actix_web::{web, App, Error, HttpRequest, HttpResponse, HttpServer};
use actix_web_actors::ws;
use reqwest::Method;
use serde_json::json;
use std::collections::HashMap;
use uuid::Uuid;
use serde_json::Value;
use sha2::{Sha512, Digest};
use tokio::sync::Mutex;
use std::sync::Arc;

const DIRECTORY_SECRET: &str = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const CLOUD_TOKEN: &str = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID: &str = "04cfba67-e965-4899-bcb9-b7497cc6863b";
const SERVER_SECRET: &str = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";
const PASSWORD_SALT: &str = "aiapd8tfa3pd8tfn3pad8tap3d84t3q4pntardi4tad4otupadrtouad37q2aioymkznsxhmytcaoeyadou37wty3ou7qjoaud37tyadou37j4ywdou7wjytaousrt7jy3t";
const MAX_PETAL_COUNT: usize = 24;

struct GameClient
{
    user: HashMap<String, serde_json::Value>,
    needs_gameserver_update: bool,
    needs_database_update: bool
}

lazy_static! {
    static ref CONNECTED_CLIENTS: Arc<Mutex<HashMap<String, GameClient>>> = Arc::new(Mutex::new(HashMap::new()));
}

fn hash(s: &str) -> String {
    let mut hasher = Sha512::new();
    hasher.update(s);
    let result = hasher.finalize();
    hex::encode(result)
}

fn is_valid_uuid(uuid: &str) -> bool {
    uuid.len() == 36 && Uuid::parse_str(uuid).is_ok()
}

fn get_rivet_url(key: &str) -> String {
    format!(
        "https://kv.api.rivet.gg/v1/entries?namespace_id={}&key={}",
        NAMESPACE_ID, key
    )
}

async fn request(
    method: Method,
    key: &str,
    body: Option<&str>,
) -> Result<serde_json::Value, reqwest::Error> {
    let url = get_rivet_url(key);
    let client = reqwest::Client::new();
    let mut request_builder = client.request(method, &url);

    if let Some(body_str) = body {
        let json_body = json!({
            "namespace_id": NAMESPACE_ID,
            "key": key,
            "value": body_str
        });
        request_builder = request_builder.json(&json_body);
    }

    request_builder = request_builder.bearer_auth(CLOUD_TOKEN);
    let response = request_builder.send().await?;
    let json_response = response.json().await?;
    Ok(json_response)
}

fn apply_missing_defaults(account: &mut HashMap<String, serde_json::Value>) {
    let mut defaults = HashMap::new();
    defaults.insert("password".to_string(), "".into());
    defaults.insert("username".to_string(), "".into());
    defaults.insert("xp".to_string(), 0.into());
    defaults.insert("petals".to_string(), serde_json::json!({"1:0": 5}));
    defaults.insert("failed_crafts".to_string(), serde_json::json!({}));
    defaults.insert("mob_gallery".to_string(), serde_json::json!({}));
    defaults.insert("inflated_up_to".to_string(), 1.into());

    for (key, value) in &defaults {
        account.entry(key.clone()).or_insert(value.clone());
    }

    account.retain(|key, _| defaults.contains_key(key));

    if account.get("inflated_up_to").unwrap().as_u64().unwrap() < MAX_PETAL_COUNT as u64 {
        println!("inflated acc:\t{}", account.get("username").unwrap());
        let inflated_up_to = account.get("inflated_up_to").unwrap().as_u64().unwrap() as usize;
        let failed_crafts = account
            .get_mut("failed_crafts")
            .unwrap()
            .as_object_mut()
            .unwrap();
        for i in inflated_up_to..MAX_PETAL_COUNT {
            for j in 0..5 {
                let key = format!("{}:{}", i, j);
                let min_value = match j {
                    0 | 1 => 4,
                    2 => 6,
                    3 => 8,
                    4 => 10,
                    _ => 0,
                };
                let entry = failed_crafts.entry(key.clone()).or_insert(min_value.into());
                *entry = serde_json::json!(std::cmp::max(min_value, entry.as_u64().unwrap()));
            }
        }
        *account.get_mut("inflated_up_to").unwrap() = MAX_PETAL_COUNT.into();
    }
}

async fn db_write_entry(username: &str, data: &Value) -> Result<(), reqwest::Error> {
    let url = format!("{}/game/players/{}", DIRECTORY_SECRET, username);
    request(Method::PUT, &url, Some(&data.to_string())).await.map(|_| ())
}

async fn db_read_user(username: &str, password: &str) -> Result<Option<Value>, reqwest::Error> {
    let connected_clients = CONNECTED_CLIENTS.lock().await;

    if let Some(client) = connected_clients.get(username) {
        if client.password == password || password == SERVER_SECRET {
            return Ok(Some(client.user.clone()));
        }
    }
    let url = format!("{}/game/players/{}", DIRECTORY_SECRET, username);
    let user_response = request(Method::GET, &url, None).await?;
    let mut user = match user_response.get("value") {
        Some(value) => value.clone(),
        None => return Ok(None),
    };
    if password != SERVER_SECRET && password != user["password"].as_str().unwrap_or("") {
        return Ok(None);
    }
    apply_missing_defaults(&mut user.as_object_mut().unwrap());
    Ok(Some(user))
}

async fn db_read_or_create_user(username: &str, password: &str) -> Result<Value, reqwest::Error> {
    if let Some(client) = CONNECTED_CLIENTS.get(username) {
        if client.password == password || password == SERVER_SECRET {
            return Ok(client.user.clone());
        }
    }
    let url = format!("{}/game/players/{}", DIRECTORY_SECRET, username);
    let user_response = request(Method::GET, &url, None).await?;
    if user_response.get("value").is_none() {
        println!("account create: {}", username);
        let mut user = HashMap::new();
        apply_missing_defaults(&mut user);
        user.insert("password".to_string(), hash(&(username.to_owned() + PASSWORD_SALT)).into());
        user.insert("username".to_string(), username.to_string().into());
        db_write_entry(username, &Value::Object(user.clone())).await?;
        Ok(Value::Object(user))
    } else {
        let mut user = user_response["value"].clone();
        apply_missing_defaults(&mut user.as_object_mut().unwrap());
        Ok(user)
    }
}

struct MyWs;

impl Actor for MyWs {
    type Context = ws::WebsocketContext<Self>;
}

/// Handler for ws::Message message
impl StreamHandler<Result<ws::Message, ws::ProtocolError>> for MyWs {
    fn handle(&mut self, msg: Result<ws::Message, ws::ProtocolError>, ctx: &mut Self::Context) {
        match msg {
            Ok(ws::Message::Binary(bin)) => ctx.binary(bin),
            _ => (),
        }
    }
}

async fn live(req: HttpRequest, stream: web::Payload) -> Result<HttpResponse, Error> {
    ws::start(MyWs {}, &req, stream)
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new().route(
            &format!("/api/live/{}", SERVER_SECRET).to_string(),
            web::get().to(live),
        )
    })
    .bind(("127.0.0.1", 55554))?
    .run()
    .await
}
