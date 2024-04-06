const path = require("path");
const fs = require("fs");

const file = path.join(__dirname, "database.json");
const db = JSON.parse(fs.readFileSync(file, "utf8"));

const MAX_PETAL_COUNT = 28;
const WRITE_DB = false;

const minRarities = [0, 0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 2, 0, 0, 0, 2, 4, 1, 0, 2, 0, 1, 1, 4, 0, 1, 0, 1];
const excludePetals = [0, 1, 10, 11, 14, 16, 23, 24, 25, 26, 27];

main: for (const id in db) {
    if (id === "accounts" || id === "links") continue;
    if (id.length !== 36) {
        console.error("bad key", id);
        break;
    }
    if (!db.accounts.includes(id)) {
        console.error("not in array", id);
        break;
    }

    const acc = db[id];
    if (!acc) {
        console.error("null acc", acc, id);
        break;
    }

    const newPetals = {"1:0": 5};
    if ("1:7" in acc.petals) {
        if (acc.petals["1:7"] !== 20) {
            console.error("bad amount", acc.petals["1:7"]);
            break;
        }
    } else {
        for (let petal = 0; petal < MAX_PETAL_COUNT; petal++) {
            for (let rarity = 0; rarity < 8; rarity++) {
                const item = `${petal}:${rarity}`;
                if (item in acc.petals) {
                    const amount = acc.petals[item];
                    if (petal === 0) {
                        console.error("none petal", item, amount, id);
                        break main;
                    }
                    if (amount === 0) {
                        console.error("zero amount", item, amount, id);
                        break main;
                    }

                    if (excludePetals.includes(petal)) break;
                    if (rarity < 2) continue;
                    const newRarity = rarity - 2;
                    const newItem = `${petal}:${newRarity}`;
                    if (minRarities[petal] > newRarity) continue;
                    const newAmount = rarity < 5 ? Math.max(amount - 5, 0) : amount;
                    if (newAmount) newPetals[newItem] = newAmount;
                }
            }
        }
    }

    if (Object.keys(newPetals).length > 1) {
        acc.petals = newPetals;
        acc.xp = 0;
        acc.failed_crafts = {};
        delete acc.inflated_up_to;
    } else {
        delete db[id];
        db.accounts.splice(db.accounts.indexOf(id), 1);
    }
}

if (WRITE_DB) {
    fs.writeFileSync(file, JSON.stringify(db));
    console.log("done");
} else console.log(JSON.stringify(db));
