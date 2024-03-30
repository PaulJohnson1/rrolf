// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

class GameClient
{
    constructor(user, server) 
    {
        this.user = user;
        this.server = server;
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