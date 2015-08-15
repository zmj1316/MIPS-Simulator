#pragma once
#include "Type.h"
class cpu_core;
class Latch
{
public:
    word IR;
};

class IDL : public Latch
{
public:
    byte R1, R2, Dst;
    word imme;

};
class IFS
{
public:
    cpu_core *c;
    IDL R;
    void execute();
};

class IDS
{
public:
    cpu_core *c;
};