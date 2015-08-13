#pragma once
#include "Type.h"

const word stack_seg = 0x8000;
class memory
{
public:
    memory();
    ~memory();

private:
    byte * mem;
    word sp;

};

