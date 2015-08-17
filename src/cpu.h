#pragma once
#include "Type.h"
#include "memory.h"
#include "stages.h"
class cpu_core
{
public:
    cpu_core();
    ~cpu_core();
    void run();
    word PC;
    memory mem;
    word reg[32];
    IFS ifs;
    IDS ids;
    EXS exs;
    MYS mys;
    WBS wbs;
};
