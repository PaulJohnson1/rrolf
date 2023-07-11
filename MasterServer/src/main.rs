use core::fmt;
use hyper::service::{make_service_fn, service_fn};
use std::{convert::Infallible, net::SocketAddr};

#[derive(Debug)]
enum ErrorCode {
    InvalidPath,
}

impl fmt::Display for ErrorCode {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{:?}", self)
    }
}

async fn rr_rivet_kv_get(name: String) {
    let client = reqwest::Client::new();
    let request = client.get("http://127.0.0.1:8080/".to_string() + name.as_str());
    let response = request.send().await.unwrap();
    let response = response.text().await.unwrap();
    println!("{}", response);
}

fn handle_get_petals(req: &hyper::Request<hyper::Body>) -> Result<String, ErrorCode> {
    Ok("okkkkk".to_string())
}

fn handle_api_request(req: &hyper::Request<hyper::Body>) -> Result<String, ErrorCode> {
    let uri = req.uri().path();
    match uri {
        "/get_petals" => handle_get_petals(req),
        _ => Err(ErrorCode::InvalidPath),
    }
}

async fn handle(
    req: hyper::Request<hyper::Body>,
) -> Result<hyper::Response<hyper::Body>, Infallible> {
    let path = req.uri().path();
    println!("connection with path {}", path);
    let response = handle_api_request(&req);
    match response {
        Ok(response) => Ok(hyper::Response::new(hyper::Body::from(response))),
        Err(error) => {
            let response = hyper::Response::builder()
                .status(400)
                .body(hyper::Body::from(error.to_string()))
                .unwrap();
            Ok(response)
        }
    }
}

#[tokio::main]
async fn main() {
    let addr = SocketAddr::from(([127, 0, 0, 1], 55554));
    let make_service = make_service_fn(|_conn| async { Ok::<_, Infallible>(service_fn(handle)) });
    let server = hyper::Server::bind(&addr).serve(make_service);
    if let Err(e) = server.await {
        eprintln!("server error: {}", e);
    }
    rr_rivet_kv_get("".to_string()).await;
}
