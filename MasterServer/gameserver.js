let id = parseInt('100', 36);
class GameServer
{
    alias = "100";
    rivet_server_id = "no-uuid";
    clients = new Array(64).fill(0);
    constructor()
    {
        this.alias = (id++).toString(36);
    }
}

module.exports = GameServer;