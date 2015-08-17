#pragma once
#include "Type.h"

const word stack_seg = 0x8000;
class memory
{
public:
    memory();
    ~memory();

    template <class T>
    void set(word addr, T value)
    {
        memcpy(trAddr(addr), &value, sizeof(T));
    }

    template <class T>
    T get(word addr)
    {
        T temp;
        memcpy(&temp, trAddr(addr), sizeof(T));
        return temp;
    }

private:
    byte * mem;
    word sp;
    byte* trAddr(word addr)
    {
        return mem + addr;
    }

};
