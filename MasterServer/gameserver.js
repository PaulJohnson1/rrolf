let id = parseInt('a00', 36);
class GameServer
{
    alias = "aaa";
    rivet_server_id = "";
    clients = new Array(64).fill(0);
    constructor()
    {
        this.alias = id.toString(36);
        ++id;
    }
}

module.exports = GameServer;