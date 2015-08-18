#include "memory.h"
memory::memory()
{
    mem = new byte[0x10000];
    sp = stack_seg;
    set<word>(0, 0x2009E3D5);

}

memory::~memory()
{
}
