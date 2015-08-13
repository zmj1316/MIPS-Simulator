#include "memory.h"
memory::memory()
{
    mem = new byte[0x10000];
    sp = stack_seg;
}

memory::~memory()
{
}