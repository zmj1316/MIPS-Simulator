#ifndef CPU_H
#define CPU_H
#include "Type.h"
#include "memory.h"
#include "stages.h"
class cpu_core
{
public:
    cpu_core();
    ~cpu_core();
    void run();
    word PC = 0;
    memory mem;
    word reg[32];
    IFS ifs;
    IDS ids;
    EXS exs;
    MYS mys;
    WBS wbs;
};
#endif /* CPU_H */
