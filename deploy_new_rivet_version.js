const { spawnSync } = require("child_process");
const fs = require("fs");

const version = process.argv[3];
const namespace = process.argv[2] || "prod"; // cannot be undefined if version is defined

let obfuscate_time = 0;
let deploy_time = 0;
let frontend_build_time = 0;

function obfuscate()
{
    const start = Date.now();
    spawnSync("node", ["reorder.js"], {stdio: "inherit"});
    obfuscate_time = Date.now() - start;
}

function deploy()
{
    const start = Date.now();
    let args = [];
    if (version)
        args = ["deploy", "-n", namespace, "--name", version]
    else
        args = ["deploy", "-n", namespace]
    spawnSync("rivet", args, {stdio: "inherit"});
    deploy_time = Date.now() - start;
}

function build_frontend()
{
    const start = Date.now();
    if (!fs.existsSync("frontend_release_build"))
        fs.mkdirSync("frontend_release_build");

    if (fs.readdirSync("frontend_release_build").length > 0)
        fs.rmSync(`${"frontend_release_build"}/*`, { recursive: true, force: true });

    process.chdir("frontend_release_build");
  
    spawnSync("cmake", ["../Client", "-DDEBUG_BUILD=0", "-DWASM_BUILD=1", "-DRIVET_BUILD=1"], {stdio: "inherit"});
  
    spawnSync("make", [], {stdio: "inherit"});
  
     fs.copyFileSync("rrolf-client", "../RivetStaticPage/rrolf-client");
     fs.copyFileSync("rrolf-client.wasm", "../RivetStaticPage/rrolf-client.wasm");
  
    // nginx
    fs.copyFileSync("rrolf-client", "/var/www/html/rrolf-client");
    fs.copyFileSync("rrolf-client.wasm", "/var/www/html/rrolf-client.wasm");
    process.chdir("..");
    frontend_build_time = Date.now() - start;
}

async function rr_discord_webhook_log(name, value, color = 0xff0000)
{
    const username = "deploy status";

    const payload = {
        username,
        embeds: [
            {
                color,
                title: name,
                description: value,
            },
        ],
    };

    const postData = JSON.stringify(payload);

    try
    {
        const response = await fetch("https://canary.discord.com/api/webhooks/1114420424277770250/e0cMQafY8B5cJBJ0FadAqjvjQgC43O5vVCsk58uv5y9tZB9CWYrXk-P9zdWFxljSEcds", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: postData,
      });

    if (!response.ok)
        throw new Error(`An error occurred while sending the webhook request. Status: ${response.status}`);
        return response;
    }
    catch (error)
    {
        console.error("An error occurred while sending the webhook request:", error);
    }
}

(async () => {
    await rr_discord_webhook_log("version deploying", `usually takes 30 seconds`, 0x0000ff);
    try
    {
        obfuscate();
        build_frontend();
        deploy();
    }
    catch(e)
    {
        await rr_discord_webhook_log("deploy error", `stack:\n${e.stack}`);
        return;
    }
    await rr_discord_webhook_log("version deployed", `namespace: \`${namespace}\`
version: \`${version || "default"}\`
\`obfuscation    time\`: \`${obfuscate_time / 1000}s\`
\`frontend_build time\`: \`${frontend_build_time / 1000}s\`
\`deploy         time\`: \`${deploy_time / 1000}s\``, 0x00ff00);
})();
