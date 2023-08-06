const express = require("express");
const cors = require("cors");
const rng = require("./rng");
const app = express();
const port = 55554;
const namespace = "/api";

const DIRECTORY_SECRET = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const CLOUD_TOKEN = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID = "04cfba67-e965-4899-bcb9-b7497cc6863b";
const SERVER_SECRET = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";
const PETALS_TO_UPGRADE = 5;

const CRAFT_CHANCES = [
    rng.get_magic_chance(0.5),
    rng.get_magic_chance(0.3),
    rng.get_magic_chance(0.15),
    rng.get_magic_chance(0.05),
    rng.get_magic_chance(0.03),
    rng.get_magic_chance(0.01),
    0
];
const CRAFT_XP_GAINS = [1, 10, 100, 1000, 10000, 100000, 1000000];

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
        maximum_wave: 1,
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

    account.maximum_wave = parseInt(account.maximum_wave);

    return account;
}

function craft(count, initial_fails, chance)
{
    if (chance === 0)
        return {count, successes: 0};
    let successes = 0;
    let fails = initial_fails;
    let attempts = 0;
    while (count >= PETALS_TO_UPGRADE)
    {
        attempts++;
        let this_chance = chance * (fails + 1);
        if (Math.random() < this_chance)
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
    await request("PUT", `${DIRECTORY_SECRET}/game/players/${username}`, data);
}

async function db_read_user(username, password)
{
    const user = await request("GET", `${DIRECTORY_SECRET}/game/players/${username}`);
    if (!user.value)
    {
        const user = apply_missing_defaults({});
        user.password = password;
        user.username = username;
        await write_db_entry(username, user);
        return user;
    }
    
    apply_missing_defaults(user.value);

    if (user.value.password !== password && password !== SERVER_SECRET)
        throw new Error("invalid password")

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
        res.end(e.stack);
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
        return "";
    // validate
    for (let i = 0; i < petals.length; i++)
        if (petals[i].count < PETALS_TO_UPGRADE)
            throw new Error("need at least " + PETALS_TO_UPGRADE + " in each craft entry");

    for (let i = 0; i < petals.length; i++)
        if (!(petals[i].count <= user.petals[format_id_rarity(petals[i])]))
            throw new Error("insufficient funds");

    let new_xp = 0;
    const results = [];
    for (let i = 0; i < petals.length; i++)
    {
        const {id, rarity, count} = petals[i];
        const key = format_id_rarity(petals[i]);
        const {successes, attempts, fails: new_fails, count: new_count} = craft(count, user.failed_crafts[key] || 0, CRAFT_CHANCES[rarity]);
        user.failed_crafts[key] = new_fails;
        new_xp += attempts * CRAFT_XP_GAINS[rarity];
        new_xp += successes * CRAFT_XP_GAINS[rarity + 1];
        results.push({id, rarity: rarity + 1, count: successes});
        results.push({id, rarity, count: new_count - count});
    }

    user.xp += new_xp;

    user_merge_petals(user, results);

    // format and return results
    for (let i = 0; i < results.length; i++)
        results[i] = format_id_rarity_count(results[i]);
    
    return new_xp + "|" + results.join(",");
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
        const resp = JSON.stringify(user);
        user.already_playing=0;
        await write_db_entry(username, user);
        return resp;
    });
});

app.get(`${namespace}/user_on_close/${SERVER_SECRET}/:username/:petals_string/:wave_end_str/:gallery`, async (req, res) => {
    const {username, petals_string, wave_end_str, gallery} = req.params;
    const wave_end = parseInt(wave_end_str);
    handle_error(res, async () => {
        log("user_on_close", [username, wave_end, petals_string]);
        const user = await db_read_user(username, SERVER_SECRET);
        // if (!user.already_playing)
        //     throw new Error("Player was not online when close happened");
        user_merge_petals(user, parse_id_rarity_count(petals_string));
        if (user.maximum_wave < wave_end)
            user.maximum_wave = wave_end;
        user.already_playing=0;
        await write_db_entry(username, user);
        return "success";
    });
});

app.get(`${namespace}/user_get/:username/:password`, async (req, res) => {
    const {username, password} = req.params;
    log("user_get", [username]);
    handle_error(res, async () => {
        const user = await db_read_user(username, password);
        delete user.failed_crafts;
        delete user.password;
        delete user.already_playing;
        return JSON.stringify(user)
    });
});

app.get(`${namespace}/user_craft_petals/:username/:password/:petals_string`, async (req, res) => {
    const {username, password, petals_string} = req.params;
    handle_error(res, async () => {
        log("crafted petals", [username, petals_string])
        const petals = parse_id_rarity_count(petals_string);
        const user = await db_read_user(username, password);
        const results = craft_user_petals(user, petals);
        await write_db_entry(username, user);
        return results;
    })
});

app.use((req, res) => {
    res.status(404).send("404 Not Found\n");
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
