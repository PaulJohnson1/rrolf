// some random guy's code
// https://gaming.stackexchange.com/questions/161430/calculating-the-constant-c-in-dota-2-pseudo-random-distribution

function CfromP(p)
{
    let Cupper = p;
    let Clower = 0;
    let Cmid;
    let p1;
    let p2 = 1;
    while (true)
    {
        Cmid = (Cupper + Clower) / 2;
        p1 = PfromC(Cmid);
        if (Math.abs(p1 - p2) <= 0) break;

        if (p1 > p) {
            Cupper = Cmid;
        }
        else {
            Clower = Cmid;
        }

        p2 = p1;
    }

    return Cmid;
}

function PfromC(C)
{
    let pProcOnN = 0;
    let pProcByN = 0;
    let sumNpProcOnN = 0;

    let maxFails = Math.ceil(1 / C);
    for (let N = 1; N <= maxFails; ++N) {
        pProcOnN = Math.min(1, N * C) * (1 - pProcByN);
        pProcByN += pProcOnN;
        sumNpProcOnN += N * pProcOnN;
    }

    return (1 / sumNpProcOnN);
}

module.exports = { get_magic_chance: CfromP, from_magic_chance: PfromC };
