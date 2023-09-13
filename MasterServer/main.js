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

function format_id_rarity_count(entry)
{
    return entry.id + ":" + entry.rarity + ":" + entry.count; 
}

function format_id_rarity(entry)
{
    return `${entry.id}:${entry.rarity}`;
}

function log(type, args)
{
    // todo: save to some sort of log file
    console.log(`${new Date().toJSON()}::[${type}]:\t${args.join("\t")}`);
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

function craft(count, initial_fails, chance)
{
    let successes = 0;
    let fails = initial_fails;
    let attempts = 0;
    if (chance === 0)
        return {count, successes, attempts, fails};
    while (count >= PETALS_TO_UPGRADE)
    {
        attempts++;
        if (Math.random() < chance * (fails + 1))
        {
            fails = 0;
            successes++;
            count -= PETALS_TO_UPGRADE;
        }
        else
        {
            fails++;
            count -= ((Math.random() * (PETALS_TO_UPGRADE - 1)) | 0) + 1;
        }
    }

    return {count, successes, attempts, fails};
}

async function write_db_entry(username, data)
{
    changed = true;
    //delete data.needs_update;
    database[username] = structuredClone(data);
    // await request("PUT", `${DIRECTORY_SECRET}/game/players/${username}`, data);
}

async function db_read_user(username, password)
{
    if (connected_clients[username] && (1 || password === SERVER_SECRET))
        return connected_clients[username].user;
    const user = structuredClone({value: database[username]});
    // const user = await request("GET", `${DIRECTORY_SECRET}/game/players/${username}`);
    if (!user.value)
    {
        const user = apply_missing_defaults({});
        user.password = password;
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

function craft_user_petals(user, petals)
{
    if (petals.length === 0)
        return "\x00error";
    // validate
    for (let i = 0; i < petals.length; i++)
        if (petals[i].count < PETALS_TO_UPGRADE)
            throw new Error("need at least " + PETALS_TO_UPGRADE + " in each craft entry");

    for (let i = 0; i < petals.length; i++)
        if (!(petals[i].count <= user.petals[format_id_rarity(petals[i])]))
            throw new Error("insufficient funds");

    const writer = new protocol.BinaryWriter();
    let new_xp = 0;
    const results = [];
    for (let i = 0; i < petals.length; i++)
    {
        const {id, rarity, count} = petals[i];
        const key = format_id_rarity(petals[i]);
        const {successes, attempts, fails: new_fails, count: new_count} = craft(count, user.failed_crafts[key] || 0, CRAFT_CHANCES[rarity]);
        user.failed_crafts[key] = new_fails;
        new_xp += attempts * CRAFT_XP_GAINS[rarity];
        //new_xp += 0.5 * successes * CRAFT_XP_GAINS[rarity + 1];
        results.push({id, rarity: rarity + 1, count: successes});
        results.push({id, rarity, count: new_count - count});
        writer.WriteUint8(id);
        writer.WriteUint8(rarity);
        writer.WriteVarUint(count - new_count);
        writer.WriteVarUint(successes);
    }
    writer.WriteUint8(0);
    writer.WriteFloat64(new_xp);

    user.xp += new_xp;

    user_merge_petals(user, results);
    
    return writer.data.subarray(0, writer.at);
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

app.get(`${namespace}/user_on_open/${SERVER_SECRET}/:username`, async (req, res) => {
    const {username} = req.params;
    handle_error(res, async () => {
        log("user_on_open", [username]);
        const user = await db_read_user(username, SERVER_SECRET);
        await write_db_entry(username, user);
        const out = new protocol.BinaryWriter();
        out.WriteStringNT(username);
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

app.get(`${namespace}/user_on_open_json/${SERVER_SECRET}/:username`, async (req, res) => {
    const {username} = req.params;
    handle_error(res, async () => {
        log("user_on_open", [username]);
        const user = await db_read_user(username, SERVER_SECRET);
        await write_db_entry(username, user);
        return JSON.stringify(user);
    });
});

app.get(`${namespace}/user_on_close/${SERVER_SECRET}/:username/:petals_string/:wave_end_str/:gallery`, async (req, res) => {
    const {username, petals_string, wave_end_str, gallery} = req.params;
    const wave_end = parseInt(wave_end_str);
    handle_error(res, async () => {
        log("user_on_close", [username, wave_end, petals_string]);
        const user = await db_read_user(username, SERVER_SECRET);

        user_merge_petals(user, parse_id_rarity_count(petals_string));
        await write_db_entry(username, user);
        return "success\x00";
    });
});

app.get(`${namespace}/user_get/:username/:password`, async (req, res) => {
    const {username, password} = req.params;
    log("user_get", [username]);
    handle_error(res, async () => {
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
        const a = await db_read_user(old_username, old_password);
        await db_read_user(username, password); // to create or verify that the new account has valid password
        a.password = password;
        a.username = username;
        await write_db_entry(username, a);

        return "success";
    });
});

app.get(`${namespace}/user_craft_petals/:username/:password/:petals_string`, async (req, res) => {
    const {username, password, petals_string} = req.params;
    handle_error(res, async () => {
        log("crafted petals", [username, petals_string])
        const petals = parse_id_rarity_count(petals_string);
        const user = await db_read_user(username, password);
        const results = craft_user_petals(user, petals);
        if (connected_clients[username])
            connected_clients[username].needs_gameserver_update = 1;
        await write_db_entry(username, user);
        return results;
    })
});

app.get(`${namespace}/user_create_squad/:username/:password`, async (req, res) => {
    const {username, password} = req.params;
    log("user_get", [username]);
    handle_error(res, async () => {
        const user = await db_read_user(username, password);
        return JSON.stringify(user);
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
                try {
                    const user = await db_read_user(uuid, SERVER_SECRET);
                    log("client init", [uuid]);
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
                const pos = decoder.ReadUint8();
                if (game_server.clients[pos] === uuid)
                {
                    log("client delete", [uuid]);
                    const client = connected_clients[uuid];
                    if (client.needs_database_update)
                        write_db_entry(client.user.username, client.user);
                    delete connected_clients[uuid];
                    game_server.clients[pos] = 0;
                }
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
                const amount = decoder.ReadUint8();
                for (let u = 0; u < amount; ++u)
                {
                    const id = decoder.ReadUint8();
                    const rarity = decoder.ReadUint8();
                    const key = id + ":" + rarity;
                    if (!user.petals[key])
                        user.petals[key] = 1;
                    else
                        ++user.petals[key];
                }
                user.needs_database_update = 1;
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
    const encoder = new protocol.BinaryWriter();
    encoder.WriteUint8(0);
    encoder.WriteStringNT(game_server.alias);
    ws.send(encoder.data.subarray(0, encoder.at));
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
    }, 2500);
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

setInterval(() => {
    log("updating db", Object.keys(connected_clients))
    for (const uuid in connected_clients)
    {
        const client = connected_clients[uuid];
        if (!client.needs_database_update)
            continue;
        client.needs_database_update = 0;
        log("updating db", uuid);
        write_db_entry(client.user.username, client.user);
    }
}, 15000);
