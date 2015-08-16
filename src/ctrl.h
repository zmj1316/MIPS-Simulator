#pragma once
#include "Type.h"
#include <iostream>
#include <map>
typedef struct _ctrl{
    char name[9];
    const byte ALUop;
    const byte ALUSrcA;
    const byte ALUSrcB;
    const byte RegDst;
    const bool MemtoReg;
    const bool RegWrite;
    const bool MemRead;
    const bool MemWrite;
    const byte PCSourse;
    const bool PCWriteCond;
    const bool PCWrite;
    
}ctrl;

const ctrl ctrls[] = {
    /*Name      , ALUop,SA,SB,RegDst,MemReg,  RegW,  MemR,  MemW,PC_S,  PCWC,  PCW*/
    { "  R-type",     1, 1, 0,     1, false,  true, false, false,   0, false, false },
    { "      LW",     0, 1, 2,     0,  true,  true,  true, false,   0, false, false },
    { "      SW",     0, 1, 2,     0, false, false, false,  true,   0, false, false },
    { "     BEQ",     0, 0, 3,     0, false, false, false, false,   0,  true, false },
    { "     BNE",     0, 0, 3,     0, false, false, false, false,   0,  true, false },
    { "    JUMP",     0, 0, 3,     0, false, false, false, false,   2, false,  true },
    { "     JAL",     0, 0, 3,     2, false,  true, false, false,   2, false,  true },
    { "      JR",     0, 1, 0,     0, false, false, false, false,   0, false,  true },
    { "    ADDI",     0, 1, 2,     0, false,  true, false, false,   0, false, false },
};

std::map<byte, ctrl> ctrlDict;