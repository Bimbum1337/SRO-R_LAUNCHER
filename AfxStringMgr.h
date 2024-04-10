//
// Created by maximus on 4/10/2024.
//

#pragma once

#include "../Lib.h"

class CAfxStringMgr : public ATL::IAtlStringMgr {
public:
    ///\address 0x00461821
    static CAfxStringMgr* Get() {
        return &*reinterpret_cast<CAfxStringMgr*>(0x04D7B5C);
    }
};


