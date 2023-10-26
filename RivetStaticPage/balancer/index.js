const rr_rarity_id_max = 7;

const canvas = document.createElement("canvas");
const ctx = canvas.getContext('2d');
for (let i = 0; i < rr_rarity_id_max; ++i)
    {
        document.getElementById("d" + i).value = 3;
        document.getElementById("m" + i).value = 3;
    }
canvas.width = canvas.height = 1000;
document.body.appendChild(canvas);
ctx.setTransform(1,0,0,1,0,0);
ctx.fillRect(100,100,100,100);
ctx.fillRect(50,50,100,100);

let RR_DROP_RARITY_COEFFICIENTS = [0, 1, 8, 8, 8, 8, 20, 3];
let RR_MOB_RARITY_COEFFICIENTS = [3, 3, 3, 3, 3, 3, 15];

function init_rarity_coefficients()
{
    for (let i = 0; i < rr_rarity_id_max; ++i)
    {
        RR_DROP_RARITY_COEFFICIENTS[i + 1] = parseInt(document.getElementById("d" + i).value);
        RR_MOB_RARITY_COEFFICIENTS[i] = parseInt(document.getElementById("m" + i).value);
    }
    let sum = RR_DROP_RARITY_COEFFICIENTS[1];
    for (let a = 1; a < rr_rarity_id_max; ++a)
    {
        sum += (RR_DROP_RARITY_COEFFICIENTS[a + 1] = RR_DROP_RARITY_COEFFICIENTS[a] / RR_DROP_RARITY_COEFFICIENTS[a + 1]);
        RR_MOB_RARITY_COEFFICIENTS[a] *= RR_MOB_RARITY_COEFFICIENTS[a - 1];
    }
    for (let a = 1; a <= rr_rarity_id_max; ++a)
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum + RR_DROP_RARITY_COEFFICIENTS[a - 1];
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_max] = 1;

}

const names = ["none","common","unusual","rare","epic","legendary","mythic","exotic"]
function loop()
{
    let seed = parseFloat(document.getElementById("seed").value);
    init_rarity_coefficients();
    canvas.width = canvas.width;
    ctx.setTransform(1,0,0,1,0,200);
    ctx.font = '10px Ubuntu';
    ctx.lineWidth = 2;
    ctx.fillStyle = '#ffffff';
    ctx.strokeStyle = '#000000';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    for (let mob = 0; mob < rr_rarity_id_max; ++mob)
    {
        let cap = mob == 0 ? 1 : mob > 4 ? mob == 6 ? 5 : 4 : mob;
        const text = (100 * Math.pow(1 - seed, RR_MOB_RARITY_COEFFICIENTS[mob])).toFixed(2) + "%";
        ctx.strokeText(text, 30, 15 + mob * 15);
        ctx.fillText(text, 30, 15 + mob * 15);
        for (let drop = 0; drop <= cap; ++drop)
        {
            let start = RR_DROP_RARITY_COEFFICIENTS[drop];
            let end = drop == cap ? 1 : RR_DROP_RARITY_COEFFICIENTS[drop + 1];
            const text = (100 * (Math.pow(1 - (1 - end) * seed, RR_MOB_RARITY_COEFFICIENTS[mob]) - Math.pow(1 - (1 - start) * seed, RR_MOB_RARITY_COEFFICIENTS[mob]))).toFixed(2) + "%";
            ctx.strokeText(text, 90 + drop * 60, 15 + mob * 15);
            ctx.fillText(text, 90 + drop * 60, 15 + mob * 15);
        }
    }
    requestAnimationFrame(loop);
}

loop();
