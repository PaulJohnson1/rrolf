const crypto = require("crypto");

const hash = s => crypto.createHash("sha512").update(s, "utf8").digest("hex");
const PASSWORD_SALT = "aiapd8tfa3pd8tfn3pad8tap3d84t3q4pntardi4tad4otupadrtouad37q2aioymkznsxhmytcaoeyadou37wty3ou7qjoaud37tyadou37j4ywdou7wjytaousrt7jy3t";
const SERVER_SECRET = "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y";

let dpw = (uuid) => hash(uuid + PASSWORD_SALT);
const link = (o, n) => {
    fetch("https://rrolf.io/api/account_link/" + o + "/" + SERVER_SECRET + "/" + n + "/" + dpw(n))}

const bddd = link("806588b1-f2fb-4f9e-b96b-d0152116a587","debe1403-78ee-4b1f-a6c3-58773bbf5961")
