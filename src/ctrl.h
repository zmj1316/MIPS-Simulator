#ifndef CTRL_H
#define CTRL_H
#include "Type.h"
#include <iostream>
#include <map>
typedef struct _ctrl_{
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


extern ctrl ctrls[];
extern std::map<byte, ctrl*> ctrlDict;;

#endif /* CTRL_H */
