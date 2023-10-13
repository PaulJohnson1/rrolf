const express = require("express");
const cors = require("cors");
const path = require("path");
const fs = require("fs");
const WSS = require("ws");
const http = require("http")
const crypto = require("crypto");
const rng = require("./rng");
const protocol = require("./protocol");
const GameServer = require("./gameserver");
const GameClient = require("./client");
const app = express();
const port = 55555;
const namespace = "/api";

const DIRECTORY_SECRET = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const PASSWORD_SALT = "aiapd8tfa3pd8tfn3pad8tap3d84t3q4pntardi4tad4otupadrtouad37q2aioymkznsxhmytcaoeyadou37wty3ou7qjoaud37tyadou37j4ywdou7wjytaousrt7jy3t";
const CLOUD_TOKEN = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID = "04cfba67-e965-4899-bcb9-b7497cc6863b";
const SERVER_SECRET = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";
const PETALS_TO_UPGRADE = 5;

const hash = s => crypto.createHash("sha512").update(s, "utf8").digest("hex");

const CRAFT_CHANCES = [
    rng.get_magic_chance(0.5),
    rng.get_magic_chance(0.3),
    rng.get_magic_chance(0.15),
    rng.get_magic_chance(0.05),
    rng.get_magic_chance(0.03),
    rng.get_magic_chance(0.01),
    0
];

const CRAFT_XP_GAINS = [1, 8, 60, 750, 25000, 1000000];

let database = {};
let changed = false;
const databaseFilePath = path.join(__dirname, "database.json");
if (fs.existsSync(databaseFilePath))
{
   const databaseData = fs.readFileSync(databaseFilePath, "utf8");
   database = JSON.parse(databaseData);
}

app.use(cors());

app.use(function (req, res, next) {
    res.setHeader("X-Powered-By", "custom rrolf http server written in c")
    next();
});

function is_valid_uuid(uuid)
{
    return uuid.length === 36 && uuid.match(/[0-9a-z]{8}-([0-9a-z]{4}-){3}[0-9a-z]{12}/) !== null;
}

function format_id_rarity_count(entry)
{
    return entry.id + ":" + entry.rarity + ":" + entry.count; 
}

function format_id_rarity(entry)
{
    return `${entry.id}:${entry.rarity}`;
}

function log(type, args, color = 31)
{
    // todo: save to some sort of log file
    console.log(`\u001b[${color}[${new Date().toJSON()}::[${type}]:\t${args.join("\t")}\u001b[0m`);
}

function get_rivet_url(key)
{
    return `https://kv.api.rivet.gg/v1/entries?namespace_id=${NAMESPACE_ID}&key=${key}`;
}

async function request(method, key, body)
{
    const url = get_rivet_url(key);
    const data_j = await fetch(url, {
        method,
        headers: {
            Authorization: `Bearer ${CLOUD_TOKEN}`
        },
        body: (() => {
            if (method !== "GET")
            {
                let json = {
                    namespace_id: NAMESPACE_ID,
                    key,
                    value: body
                };

                return JSON.stringify(json);
            }
        })()
    });

    const data = await data_j.json();
    return data;
}

/*
reason this one is better than the rust one:
in the rust version, users were passed around by the username.passwor, this
only passes around the accounst object instead which results in fewer requests
*/
function apply_missing_defaults(account)
{
    const defaults = {
        password: "",
        username: "",
        xp: 0,
        already_playing: 0,
        petals: {"1:0": 5},
        failed_crafts: {},
        mob_gallery: {}
    };

    account.user_playing = 0;

    // Fill in any missing defaults
    for (let prop in defaults) {
        if (!account.hasOwnProperty(prop)) {
            account[prop] = defaults[prop];
        }
    }

    // Remove any extra properties
    for (let prop in account) {
        if (!defaults.hasOwnProperty(prop)) {
            delete account[prop];
        }
    }

    return account;
}

async function write_db_entry(username, data)
{
    changed = true;
    //delete data.needs_update;
    //database[username] = structuredClone(data);
    await request("PUT", `${DIRECTORY_SECRET}/game/players/${username}`, data);
}

async function db_read_user(username, password)
{
    //const user = structuredClone({value: database[username]});
    const user = await request("GET", `${DIRECTORY_SECRET}/game/players/${username}`);
    if (!user.value)
    {
        const user = apply_missing_defaults({});
        user.password = hash(username + PASSWORD_SALT);
        user.username = username;
        await write_db_entry(username, user);
        return user;
    }
    apply_missing_defaults(user.value);
    return user.value;
}

async function handle_error(res, cb)
{
    try
    {
        res.end(await cb());
    }
    catch (e)
    {
        console.log(e);
        res.end("\x00" + e.stack);
    }
}


const server = http.createServer(app);

server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});


const FORCE_LINK = async (old_username, username) => {
    log("account_link", [old_username, username]);
    if (!is_valid_uuid(old_username) || !is_valid_uuid(username))
        throw new Error("invalid uuid");
    const a = await db_read_user(old_username, SERVER_SECRET);
    const new_account = await request("GET", `${DIRECTORY_SECRET}/game/players/${username}`);
    if (!new_account.value || 1)
    {
        a.password = hash(username + PASSWORD_SALT);
        a.username = username;
        console.log(a);
        await write_db_entry(username, a);
    }
    console.log("lol");
    return "success";
};

const d = FORCE_LINK("5454df82-8233-44bd-8b27-c8f59bb190f3","8ed1216f-c508-4356-b43a-d07d00068410");
console.log(d);