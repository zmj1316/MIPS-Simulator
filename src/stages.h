#ifndef STAGES_H
#define STAGES_H
#include "Type.h"
#include <iostream>
#include "ctrl.h"

#define OP_MASK    0xFC000000
#define RS_MASK    0x03E00000
#define RT_MASK    0x001F0000
#define RD_MASK    0x0000F800
#define SHAMT_MASK 0x000007C0
#define FUNC_MASK  0x0000003F
#define IMME_MASK  0x0000ffff

class cpu_core;
class Latch
{
public:
    word IR;
    ctrl *control()
    {
        if ((IR & 0xFC1FFFFF) == 8)
            return &(ctrls[7]);
        return ctrlDict[IR >> 26];
    }
};

class IDL : public Latch
{
public:
    byte RS, RT, RD;
    word imme;
    word PC;
};

class DEL :public Latch
{
public:
    byte Dst;
    word RA, RB, imme;
    word PC;
};

class EML :public Latch
{
public:
    byte Dst;
    word alures, RB;
};

class MWL :public Latch
{
public:
    byte Dst;
    word alures, RB, MDR;
};
class IFS
{
public:
    cpu_core *c;
    IDL R;
    IFS(cpu_core *c) :c(c)
    {
        init();
    }
    void init()
    {
        memset(&R, 0, sizeof(IDL));
    }
    void execute();
};

class IDS
{
public:
    cpu_core *c;
    IDL L;
    DEL R;
    IDS(cpu_core *c) :c(c)
    {
        init();
    }
    void init()
    {
        memset(&L, 0, sizeof(IDL));
        memset(&R, 0, sizeof(DEL));
    }
    void execute();
    void shift();
};

class EXS
{
public:
    cpu_core *c;
    DEL L;
    EML R;
    EXS(cpu_core *c) :c(c)
    {
        init();
    }
    void init()
    {
        memset(&L, 0, sizeof(DEL));
        memset(&R, 0, sizeof(EML));
    }
    void execute();
    void shift();
};

class MYS
{
public:
    cpu_core *c;
    EML L;
    MWL R;
    MYS(cpu_core *c) :c(c)
    {
        init();
    }
    void init()
    {
        memset(&L, 0, sizeof(EML));
        memset(&R, 0, sizeof(MWL));
    }
    void execute();
    void shift();

};
class WBS
{
public:
    cpu_core *c;
    MWL L;
    WBS(cpu_core *c) :c(c)
    {
        init();
    }
    void init()
    {
        memset(&L, 0, sizeof(MWL));
    }
    void execute();
    void shift();
};
#endif /* STAGES_H */
