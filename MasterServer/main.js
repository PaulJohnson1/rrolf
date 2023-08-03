const express = require("express");
const cors = require("cors");
const app = express();
app.use(cors());
const port = 55554;
const namespace = "/api";

const DIRECTORY_SECRET = "a92pd3nf29d38tny9pr34dn3d908ntgb";
const CLOUD_TOKEN = "cloud.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CKOM_-XtMRCjtLqo-DAaEgoQjUflOmYrT3Sv5ckk4-Nk0yIWOhQKEgoQ6l7BiqssS-iYCw6PaqKKnA.Pgw_qDBaugBIFd7ilYcbbm_6yPNDeqreiDi1VBkKX84ER7CXvS-8abNuRhKtU_hDtgT9Sd4a7JWN68fdLnEKCA";
const NAMESPACE_ID = "04cfba67-e965-4899-bcb9-b7497cc6863b";
const SERVER_SECRET = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";
const PETALS_TO_UPGRADE = 5;

const CRAFT_CHANCES = [0.5, 0.3, 0.15, 0.05, 0.03, 0.01, 0];

app.use(function (req, res, next) {
    res.removeHeader("X-Powered-By");
    res.appendHeader("X-Powered_By", "nginx")
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
    console.log(`${new Date().toJSON()}::[${type}]: ${args.join("/")}`);
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
    if (!account.password) account.password = "";
    if (!account.username) account.username = "";
    if (!account.maximum_wave) account.maximum_wave = 1;
    if (!account.xp) account.xp = 1;
    if (!account.petals) account.petals = {"1:0": 5};
    if (!account.petal_crafts) account.petal_crafts = {};
    if (!account.mob_gallery) account.mob_gallery = {};

    return account;
}

function craft(count, chance)
{
    if (chance === 0)
        return {count, successes: 0};
    let successes = 0;
    while (count >= PETALS_TO_UPGRADE)
    {
        if (Math.random() < chance)
        {
            successes++;
            count -= PETALS_TO_UPGRADE;
        }
        else
            count -= ((Math.random() * (PETALS_TO_UPGRADE - 1)) | 0) + 1;
    }

    return {count, successes};
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
        if (petals[i].count > user.petals[format_id_rarity(petals[i])])
            throw new Error("insufficient funds");

    const results = [];
    for (let i = 0; i < petals.length; i++)
    {
        const {id, rarity, count} = petals[i];
        const {successes, count: new_count} = craft(count, CRAFT_CHANCES[rarity]);
        results.push({id, rarity: rarity + 1, count: successes});
        results.push({id, rarity, count: new_count - count});
    }

    user_merge_petals(user, results);

    // format and return results
    for (let i = 0; i < results.length; i++)
        results[i] = format_id_rarity_count(results[i]);
    
    return results.join(",");
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

app.get(`${namespace}/user_on_close/${SERVER_SECRET}/:username/:petals_string/:wave_end/:gallery`, async (req, res) => {
    const {username, petals_string, wave_end, gallery} = req.params;
    handle_error(res, async () => {
        log("user_on_close", [username, wave_end, petals_string]);
        const user = await db_read_user(username, SERVER_SECRET);
        user_merge_petals(user, parse_id_rarity_count(petals_string));
        if (!(user.maximum_wave > wave_end)) user.maximum_wave = wave_end;
        await write_db_entry(username, user);
        return "success";
    });
});

app.get(`${namespace}/user_get/:username/:password`, async (req, res) => {
    const {username, password} = req.params;
    log("user_get", [username]);
    handle_error(res, async () => JSON.stringify(await db_read_user(username, password)));
});

app.get(`${namespace}/user_craft_petals/:username/:password/:petals_string`, async (req, res) => {
    const {username, password, petals_string} = req.params;
    handle_error(res, async () => {
        log("crafted petals", [petals_string])
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
