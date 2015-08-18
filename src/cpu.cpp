#include "cpu.h"

cpu_core::cpu_core() : ifs(this), ids(this), exs(this), mys(this), wbs(this)
{
}

cpu_core::~cpu_core()
{
}

void cpu_core::run()
{
    ctrlDict[0] = &ctrls[0];
    ctrlDict[35] = &ctrls[1];
    ctrlDict[43] = &ctrls[2];
    ctrlDict[4] = &ctrls[3];
    ctrlDict[5] = &ctrls[4];
    ctrlDict[2] = &ctrls[5];
    ctrlDict[3] = &ctrls[6];
    ctrlDict[8] = &ctrls[8];
    ifs.execute();
    ids.shift();
    ids.execute();
    exs.shift();
    exs.execute();
    mys.shift();
    mys.execute();
    wbs.shift();
    wbs.execute();
    printf("%u", reg[9]);
}
