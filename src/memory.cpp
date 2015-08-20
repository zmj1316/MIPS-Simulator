#include "memory.h"
memory::memory()
{
    mem = new byte[0x10000];
    sp = stack_seg;
    set<word>(0, 0x20090001); //$t1=1
    set<word>(4, 0x200A0005); //$t2=5
    set<word>(8, 0x21290001); //$t1+=1
    set<word>(12, 0x11490001); //beq $t1 $t2
    set<word>(16, 0x8000002); //j 2
    set<word>(20, 0x20090001); //$t1=1
}

memory::~memory()
{
    delete[] mem;
}
