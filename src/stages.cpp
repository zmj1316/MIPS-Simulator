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
    c->PC += 4;
    R.PC = c->PC;
    R.IR = IR;
    R.R1 = IR&RS_MASK >> 21;
    R.R2 = IR&RT_MASK >> 16;
    R.Dst = IR&RD_MASK >> 11;
    R.imme = IR&IMME_MASK;
}

void IDS::execute()
{
    R.IR = L.IR;
    R.RA = c->reg[L.R1];
    R.RB = c->reg[L.R2];
    R.imme = L.imme;
    /*Sign extend*/
    if (R.imme & 0x8000 == 0x8000)
    {
        R.imme |= 0xffff0000;
    }
    R.PC = L.PC;
}

void EXS::execute()
{
    R.IR = L.IR;
    R.RB = L.RB;
    ctrl *C = L.control();
    /*ALU Part*/
    word A = C->ALUSrcA ? L.RA : L.PC;
    word B = 0;
    switch (C->ALUSrcB)
    {
    case 0:
        B = L.RB;
        break;
    case 1:
        B = 4;
        break;
    case 2:
        B = L.imme;
        break;
    case 3:
        B = L.imme << 2;
        break;
    }
    switch (C->ALUop)
    {
    case 0:
        R.alures = A + B;
        break;
    case 1:
        /*ALU Func*/
    default:
        break;
    }
    if (C->PCWrite)
    {
        c->PC = C->PCSourse == 0 ? R.alures : (L.IR << 6 >> 4) | (c->PC & 0xF0000000);
        c->ifs.init();
        c->ids.init();
    }
    if (C->PCWriteCond)
    {
        bool taken;
        switch (L.IR>>26)
        {
        case 4:
            taken = L.RA == L.RB;
        case 5:
            taken = L.RA != L.RB;
        default:
            break;
        }
        if (taken)
        {
            c->PC = R.alures;
        }
    }
}
