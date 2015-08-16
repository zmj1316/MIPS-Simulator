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
    byte R1, R2, Dst;
    word imme;
    word PC;
};

class DEL :public Latch
{
public:
    word RA, RB, imme;
    word PC;
};

class EML :public Latch
{
public:
    word alures, RB;
};

class IFS
{
public:
    cpu_core *c;
    IDL R;
    IFS(cpu_core *c) :c(c)
    {}
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
    {}
    void init()
    {
        memset(&L, 0, sizeof(IDL));
        memset(&R, 0, sizeof(DEL));
    }
    void execute();
};

class EXS
{
public:
    cpu_core *c;
    DEL L;
    EML R;
    EXS(cpu_core *c) :c(c)
    {}
    void init()
    {
        memset(&L, 0, sizeof(DEL));
        memset(&R, 0, sizeof(EML));
    }void execute();
};

class WBS
{
public:
};