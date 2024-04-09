//
// Created by maximus on 4/9/2024.
//

#pragma once
#include "Lib.h"
#include "libs/JMX_Library/GFX/include/GFXFM/IFileManager.h"
#include "libs/JMX_Library/GFX/include/GFXFM/AutoFileManager.h"
#include "Controls/Agreement.h"

enum E_LANGUAGES : int {
    KOREA,
    CHINESE,
    TAIWAN,
    JAPAN,
    GLOBAL,
    VIETNAM,
    GERMANY,
    TURKEY,
    THAILAND,
    RUSSIA,
    SPAIN,
    ARABIC,
};

#define LANGUAGE (*(E_LANGUAGES *) 0x004C60B0)
#define g_btDivision (*(BYTE *) ((int) 0x004C607D))


#define GET_CLIENT_RECT(rect, ...) \
    reinterpret_cast<RECT& (*)(RECT&, ...)>(0x044A240)(rect, __VA_ARGS__); \


class CBSClientApp : CWinApp {
public:
    /// \address 00431F60
    int LoadFileManager();

    /// \address 00431B70
    bool ValidateProcess();

    /// \address 00431B20
    void ReleaseFileManager();
public:
    IFileManager* m_pFileManager; //0x00A4
    CAutoFileManager m_autoFileManager; //0x00A8
    CAgreement m_agreementWnd; //0x00CC
    CButton m_button; //0x0140
    char pad_0190[0x10]; //0x0190
    std::string m_strProcessName; //0x01A0
    std::string m_strTitle; //0x01BC
};

#define g_cBSClientApp (*((CBSClientApp*)0x004C5DA0))
