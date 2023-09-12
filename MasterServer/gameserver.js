let id = parseInt('a00', 36);
class GameServer
{
    server_id = "aaa";
    clients = new Array(64).fill(0);
    constructor()
    {
        this.server_id = id.toString(36);
        ++id;
    }
}

module.exports = GameServer;