const path = require("path");
const fs = require("fs");

const MAX_PETAL_COUNT = 28;
const PURGE = false;

const file = path.join(__dirname, "database.json");
const db = JSON.parse(fs.readFileSync(file, "utf8"));

console.log("total accs", db.accounts.length);
let count = 0;

main: for (const id in db) {
    if (id === "accounts" || id === "links") continue;
    if (id.length !== 36) {
        console.log("bad key", id);
        break;
    }
    if (!db.accounts.includes(id)) {
        console.log("not in array", id);
        break;
    }

    const acc = db[id];
    if (!acc) {
        console.log("null acc", acc, id);
        break;
    }

    if (acc.xp < 10000000) {
        console.log("low xp", acc.xp, id);
        break;
    }

    let newXp = acc.xp - 10000000;
    let newItems = 0;
    for (let petal = 0; petal < MAX_PETAL_COUNT; petal++) {
        for (let rarity = 0; rarity < 8; rarity++) {
            const item = `${petal}:${rarity}`;
            if (item in acc.petals) {
                const amount = acc.petals[item];
                if (petal === 0) {
                    console.log("none petal", item, amount, id);
                    break main;
                }
                if (amount === 0) {
                    console.log("zero amount", item, amount, id);
                    break main;
                }
                if (rarity >= 5) newItems += amount;
                else if (rarity >= 3) newItems += Math.max(amount - 5, 0);
            }
        }
    }

    if (newXp === 0 || newItems === 0) {
        if (PURGE) {
            delete db[id];
            db.accounts.splice(db.accounts.indexOf(id), 1);
        }
        count += 1;
    }
}

if (PURGE && count > 0) {
    fs.writeFileSync(file, JSON.stringify(db));
    console.log("purged", count, "accs");
} else console.log(count, "accs to purge");
