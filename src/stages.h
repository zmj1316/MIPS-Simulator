#pragma once
#include "Type.h"
#include <iostream>
#include "ctrl.h"
class cpu_core;
class Latch
{
public:
    word IR;
    ctrl *control()
    {
        return &ctrlDict[IR >> 26];
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
    void shift()
    {
        L = c->ifs.R;
    }
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
    void shift()
    {
        L = c->ids.R;
    }
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
    void shift()
    {
        L = c->exs.R;
    }

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
    void shift()
    {
        L = c->mys.R;
    }
};
