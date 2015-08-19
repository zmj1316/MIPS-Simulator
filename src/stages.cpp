#include "cpu.h"
#include "stages.h"


void IFS::execute()
{
    word IR = c->mem.get<word>(c->PC);
    c->PC += 4;
    R.PC = c->PC;
    R.IR = IR;
    R.RS = (IR&RS_MASK) >> 21;
    R.RT = (IR&RT_MASK) >> 16;
    R.RD = (IR&RD_MASK) >> 11;
    R.imme = (IR&IMME_MASK);
}

void IDS::execute()
{
    R.IR = L.IR;
    R.RA = c->reg[L.RS];
    R.RB = c->reg[L.RT];
    switch (R.control()->RegDst)
    {
    case 0:
        R.Dst = L.RT;
        break;
    case 1:
        R.Dst = L.RS;
        break;
    case 2:
        R.Dst = 31;
    default:
        break;
    }
    R.imme = L.imme;
    /*Sign extend*/
    if ((R.imme & 0x8000) == 0x8000)
    {
        R.imme |= 0xffff0000;
    }
    R.PC = L.PC;
}

void EXS::execute()
{
    R.IR = L.IR;
    R.RB = L.RB;
    R.Dst = L.Dst;
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

    default:
        break;
    }
    if (C->ALUop == 1)
    {
        /*ALU Func*/
        byte opcode = L.IR & 0x3F;
        switch (opcode)
        {
        case 0x20:
            R.alures = A + B;
            break;

        default:
            break;
        }
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
            break;
        case 5:
            taken = L.RA != L.RB;
            break;
        default:
            break;
        }
        if (taken)
        {
            c->PC = R.alures;
        }
    }
}

void MYS::execute()
{
    const ctrl *C = L.control();

    R.IR = L.IR;
    R.Dst = L.Dst;
    R.alures = L.alures;
    R.MDR = 0;
    if (C->MemRead)
    {
        R.MDR = c->mem.get<word>(L.alures);
    }
    else if (C->MemWrite)
    {
        c->mem.set<word>(L.alures, L.RB);
    }

}

void WBS::execute()
{
    const ctrl *C = L.control();

    if (C->RegWrite)
    {
        if (C->MemtoReg)
        {
            c->reg[L.Dst] = L.MDR;
        }
        else
        {
            c->reg[L.Dst] = L.alures;
        }
    }
    c->reg[0] = 0;
}

void IDS::shift()
{
    L = c->ifs.R;
}

void EXS::shift()
{
    L = c->ids.R;
}

void MYS::shift()
{
        L = c->exs.R;
}

void WBS::shift()
{
    L = c->mys.R;
}
