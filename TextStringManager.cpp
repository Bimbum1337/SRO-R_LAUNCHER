//
// Created by maximus on 4/9/2024.
//

#include "TextStringManager.h"

const std::string * CTextStringManager::GetString(const char *identifier) {
    return reinterpret_cast<const std::string *(__thiscall*)(CTextStringManager*, const char *identifier)>(0x0044E740)(this, identifier);
}
