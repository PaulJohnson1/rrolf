class GameClient
{
    constructor(user) 
    {
        this.user = user;
        this.needs_gameserver_update = false;
        this.needs_database_update = false;
    }

    write(encoder) 
    {
        const user = this.user;
        encoder.WriteStringNT(user.username);
        encoder.WriteFloat64(user.xp);
        for (const petal of Object.keys(user.petals))
        {
            if (!(user.petals[petal] > 0))
                continue;
            const [id, rarity] = petal.split(":");
            encoder.WriteUint8(id);
            encoder.WriteUint8(rarity);
            encoder.WriteVarUint(user.petals[petal]);
        }
        encoder.WriteUint8(0);
        for (const petal of Object.keys(user.failed_crafts))
        {
            if (!(user.failed_crafts[petal] > 0))
                continue;
            const [id, rarity] = petal.split(":");
            encoder.WriteUint8(id);
            encoder.WriteUint8(rarity);
            encoder.WriteVarUint(user.failed_crafts[petal]);
        }
        encoder.WriteUint8(0);
        this.needs_gameserver_update = false;
    }
}

module.exports = GameClient;