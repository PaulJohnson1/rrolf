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
            encoder.WriteVarUint(user.petals[petal]);
            encoder.WriteUint8(rarity);
        }
        encoder.WriteUint8(0);
        this.needs_gameserver_update = false;
    }
}

module.exports = GameClient;