//
// Created by maximus on 4/9/2024.
//

#pragma once
#include <string>

class CTextStringManager {
public:
    ///\ address 0x44E740
    const std::string * GetString(const char *identifier);
};


#define g_CTextStringManager ((CTextStringManager*)0x004C60D0)

#define TSM_GETTEXTPTR(text) (g_CTextStringManager->GetString(text)->c_str())
#define TSM_GETTEXT(text) (g_CTextStringManager->GetString(text))