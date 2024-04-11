#pragma once

#include "IClientNet.h"
#include "Msg.h"

class CClientNet : public IClientNet
{
public:
    static CClientNet* get()
    {
        return *reinterpret_cast<CClientNet**>(0x04D9F50);
    }

};

