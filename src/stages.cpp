#include "stages.h"
#include "cpu.h"

#define OP_MASK    0xFC000000
#define RS_MASK    0x03E00000
#define RT_MASK    0x001F0000
#define RD_MASK    0x0000F800
#define SHAMT_MASK 0x000007C0
#define FUNC_MASK  0x0000003F
#define IMME_MASK  0x0000ffff

void IFS::execute()
{
    word IR = c->mem.get<word>(c->PC);
    R.R1 = IR&RS_MASK >> 21;
    R.R2 = IR&RT_MASK >> 16;
    R.Dst = IR&RD_MASK >> 11;
    R.imme = IR&IMME_MASK;
}