#pragma once
#include "Type.h"
#include "memory.h"
class cpu_core
{
public:
    cpu_core();
    ~cpu_core();

    word PC;
    memory mem;

};

