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
const port = 55554;
const namespace = "/api";

const DIRECTORY_SECRET = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const PASSWORD_SALT = "aiapd8tfa3pd8tfn3pad8tap3d84t3q4pntardi4tad4otupadrtouad37q2aioymkznsxhmytcaoeyadou37wty3ou7qjoaud37tyadou37j4ywdou7wjytaousrt7jy3t";
const CLOUD_TOKEN = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID = "04cfba67-e965-4899-bcb9-b7497cc6863b";
const SERVER_SECRET = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";

const hash = s => crypto.createHash("sha512").update(s, "utf8").digest("hex");

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
    if (connected_clients[username] && (connected_clients[username].password === password || password === SERVER_SECRET))
        return connected_clients[username].user;
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

function user_merge_petals(user, petals)
{
    for (let i = 0; i < petals.length; i++)
    {
        const petal = petals[i];
        const key = format_id_rarity(petal);
        if (!user.petals[key]) user.petals[key] = petal.count;
        else user.petals[key] += petal.count;
    }
}

// example: 1:0:123,1:5:1236
function parse_id_rarity_count(string)
{
    let a = string.split(",");
    const result = [];

    for (let i = 0; i < a.length; i++)
    {
        const entry = a[i].split(":");
        if (entry.length !== 3)
            throw new Error("invalid petal entry");

        const id = parseInt(entry[0]);
        const rarity = parseInt(entry[1]);
        const count = parseInt(entry[2]);
        if (!Number.isInteger(id))
            return new Error("invalid id entry");
        if (!Number.isInteger(rarity))
            return new Error("invalid rarity entry");
        if (!Number.isInteger(count))
            return new Error("invalid count entry");

        result.push({id, rarity, count});
    }

    return result;
}

app.get(`${namespace}/user_on_open_json/${SERVER_SECRET}/:username`, async (req, res) => {
    const {username} = req.params;
    handle_error(res, async () => {
        if (!is_valid_uuid(username))
            throw new Error("invalid uuid");
        log("user_on_open", [username]);
        const user = await db_read_user(username, SERVER_SECRET);
        await write_db_entry(username, user);
        return JSON.stringify(user);
    });
});

app.get(`${namespace}/user_get/:username/:password`, async (req, res) => {
    const {username, password} = req.params;
    log("user_get", [username]);
    handle_error(res, async () => {
        if (!is_valid_uuid(username))
            throw new Error("invalid uuid");
        const user = await db_read_user(username, password);
        const out = new protocol.BinaryWriter();
        out.WriteStringNT(user.username);
        out.WriteFloat64(user.xp);
        let checksum = 5;
        for (const petal of Object.keys(user.petals))
        {
            if (!(user.petals[petal] > 0))
                continue;
            const [id, rarity] = petal.split(":");
            out.WriteUint8(id);
            out.WriteVarUint(user.petals[petal]);
            out.WriteUint8(rarity);
            checksum += parseInt(id) + ((rarity * user.petals[petal]) & 1023);
        }
        out.WriteUint8(0);
        out.WriteVarUint(checksum);
        return out.data.subarray(0, out.at);
    });
});

app.get(`${namespace}/account_link/:old_username/:old_password/:username/:password`, async (req, res) => {
    const {old_username, old_password, username, password} = req.params;
    log("account_link", [old_username, username]);
    handle_error(res, async () => {
        if (!is_valid_uuid(old_username) || !is_valid_uuid(username))
            throw new Error("invalid uuid");
        const a = await db_read_user(old_username, old_password);
        const new_account = await request("GET", `${DIRECTORY_SECRET}/game/players/${username}`);
        if (!new_account.value)
        {
            a.password = hash(username + PASSWORD_SALT);
            a.username = username;
            await write_db_entry(username, a);
        }
        return "success";
    });
});

app.get(`${namespace}/user_get_password/:password`, async (req, res) => {
    const {password} = req.params;
    handle_error(res, async () => {
        const d = await fetch("https://identity.api.rivet.gg/v1/identities/self/profile", {
            headers: {
                Authorization: "Bearer " + password
            }
        });
        if (d.status != 200)
            throw new Error(JSON.stringify(await d.text()));
        const j = await d.json();
        return hash(j.identity.identity_id + PASSWORD_SALT);
    });
});

app.get(`${namespace}/user_get_server_alias/:alias`, async (req, res) => {
    const {alias} = req.params;
    handle_error(res, async () => {
        if (game_servers[alias])
            return game_servers[alias].rivet_server_id;
        else
            return '';
    });
});


app.use((req, res) => {
    res.status(404).send("404 Not Found\n");
});

const saveDatabaseToFile = () => {
   if (changed)
   {
       changed = false;
       console.log("saving database to file:", databaseFilePath);
       const databaseData = JSON.stringify(database, null, 2);
       fs.writeFileSync(databaseFilePath, databaseData, "utf8");
   }
   else
       console.log("tried save, was not changed");
};

const server = http.createServer(app);

server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});


const wss = new WSS.Server({server});
const game_servers = {};
const connected_clients = {};

wss.on("connection", (ws, req) => {
    if (req.url !== `/api/${SERVER_SECRET}`)
       return ws.close();
    const game_server = new GameServer();
    game_server[game_server.alias] = game_server;
    ws.on('message', async (message) => {
        const data = new Uint8Array(message);
        const decoder = new protocol.BinaryReader(data);
        switch(decoder.ReadUint8())
        {
            case 0:
            {
                const uuid = decoder.ReadStringNT();
                const pos = decoder.ReadUint8();
                log("attempt init", [uuid]);
                if (!is_valid_uuid(uuid) || connected_clients[uuid])
                {
                    log("player force disconnect", [uuid]);
                    const encoder = new protocol.BinaryWriter();
                    encoder.WriteUint8(2);
                    encoder.WriteUint8(pos);
                    encoder.WriteStringNT(uuid);
                    ws.send(encoder.data.subarray(0, encoder.at));
                    break;
                }
                try {
                    const user = await db_read_user(uuid, SERVER_SECRET);
                    if (!user)
                    {
                        log("player dne disconnect", [uuid]);
                        const encoder = new protocol.BinaryWriter();
                        encoder.WriteUint8(2);
                        encoder.WriteUint8(pos);
                        encoder.WriteStringNT(uuid);
                        ws.send(encoder.data.subarray(0, encoder.at));
                        return;
                    }
                    connected_clients[uuid] = new GameClient(user);
                    game_server.clients[pos] = uuid;
                    const encoder = new protocol.BinaryWriter();
                    encoder.WriteUint8(1);
                    encoder.WriteUint8(pos);
                    connected_clients[uuid].write(encoder);
                    ws.send(encoder.data.subarray(0, encoder.at));
                } catch(e) {
                    console.log(e);
                }
                break;
            }
            case 1:
            {
                const uuid = decoder.ReadStringNT();
                const pos = game_server.clients.indexOf(uuid);
                if (pos !== -1)
                {
                    log("client delete", [uuid]);
                    const client = connected_clients[uuid];
                    if (!client)
                        break;
                    write_db_entry(client.user.username, client.user);
                    game_server.clients[pos] = 0;
                }
                delete connected_clients[uuid];
                break;
            }
            case 2:
            {
                const uuid = decoder.ReadStringNT();
                if (!connected_clients[uuid])
                    break;
                const user = connected_clients[uuid].user;
                const pos = game_server.clients.indexOf(uuid);
                if (pos === -1)
                    break;
                user.xp = decoder.ReadFloat64();
                user.petals = {};
                user.failed_crafts = {};
                let id = decoder.ReadUint8();
                while (id)
                {
                    const rarity = decoder.ReadUint8();
                    const count = decoder.ReadVarUint();
                    user.petals[id+':'+rarity] = count;
                    id = decoder.ReadUint8();
                }
                id = decoder.ReadUint8();
                while (id)
                {
                    const rarity = decoder.ReadUint8();
                    const count = decoder.ReadVarUint();
                    user.failed_crafts[id+':'+rarity] = count;
                    id = decoder.ReadUint8();
                }
                write_db_entry(user.username, user);
                break;
            }
            case 100:
                //ping
                break;
            case 101:
                game_server.rivet_server_id = decoder.ReadStringNT();
                log("server id recv", [game_server.rivet_server_id]);
                break;
        }
    });
    log("game connect", [game_server.alias]);
    game_servers[game_server.alias] = game_server;
    const encoder = new protocol.BinaryWriter();
    encoder.WriteUint8(0);
    encoder.WriteStringNT(game_server.alias);
    ws.send(encoder.data.subarray(0, encoder.at));
    /*
    setInterval(() => {
        for (let pos = 0; pos < 64; ++pos)
        {
            const uuid = game_server.clients[pos];
            if (!connected_clients[uuid])
                continue;
            const client = connected_clients[uuid];
            if (!client.needs_gameserver_update)
                continue;
            log("client update", [uuid]);
            const encoder = new protocol.BinaryWriter();
            encoder.WriteUint8(1);
            encoder.WriteUint8(pos);
            client.write(encoder);
            ws.send(encoder.data.subarray(0, encoder.at));
        }
    }, 500);
    */
    setInterval(() => {
        //ping packet
        const encoder = new protocol.BinaryWriter();
        encoder.WriteUint8(100);
        ws.send(encoder.data.subarray(0, encoder.at));
    }, 20000);
    ws.on('close', () => {
        log("game disconnect", [game_server.alias]);
        for (const uuid of game_server.clients)
            delete connected_clients[uuid];
        delete game_servers[game_server.alias];
    });
});

let quit = false;
const try_save_exit = () =>
{
   if (!quit)
   {
       quit = true;
       saveDatabaseToFile();
   }
   process.exit();
}

process.on("beforeExit", try_save_exit);
process.on("exit", try_save_exit)
process.on("SIGTERM", try_save_exit);
process.on("SIGINT", try_save_exit);
process.on("uncaughtException", try_save_exit);

setInterval(saveDatabaseToFile, 60000);

setInterval(() => {
    log("player count", [Object.keys(connected_clients).length]);
}, 15000);

const FORCE_LINK = (old_username, username) => {
log("account_link", [old_username, username]);
handle_error(res, async () => {
    if (!is_valid_uuid(old_username) || !is_valid_uuid(username))
        throw new Error("invalid uuid");
    const a = await db_read_user(old_username, SERVER_SECRET);
    const new_account = await request("GET", `${DIRECTORY_SECRET}/game/players/${username}`);
    if (!new_account.value)
    {
        a.password = hash(username + PASSWORD_SALT);
        a.username = username;
        await write_db_entry(username, a);
    }
    return "success";
})};

FORCE_LINK()