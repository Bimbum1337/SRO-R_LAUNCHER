//
// Created by maximus on 4/9/2024.
//
#pragma once

#include <vector>
#include "Lib.h"
#include "ImgScrollBar.h"

/// \address 004367B0
int GetRegisteredFile(const char*fileName, CGdiObject *pObj);

/// \address 004385C0
int RegisterFiles();

struct SDivisonInfo{
};

class CBSClientDlg : public CDialog{
public:
    /// \address 004392D0
    static int InitFiles();

    /// \address 00432720
    static void InitPath();

    /// \address 004355A0
    void RegisterDivisonKey();

    /// \address 0043A530
    BOOL OnInitDialog_IMPL();

    /// \address 00433DD0
    void CreateChildControls();

    /// \address 004375B0
    void SetBackGroundImages();

    /// \address 00434E60
    void CreateDefaultFont();

    /// \address 00434E60
    void LoadGlobalLang();

    /// \address 00434E60
    void InitGlobalLangImage();

    /// \address 00439580
    void StartGatewayService();

    /// \address 00433590
    void ShowLanguangeSelectWindow();

    /// \address 0043A0E0
    bool VerifyConnection();

    void AfterInitDialog();
public:
    char pad_0074[0x420]; //0x0074
    HWND m_dcHwnd; //0x0494
    RECT m_articleRect[3]; //0x0498
    char pad_04C8[0xA4]; //0x04C8
    CDHtmlDialog* m_pHtmlDialog; //0x056C
    CImgScrollBar m_pArticleScroll; //0x0570
    char pad_05C4[0x12C]; //0x05C4
    std::vector<SDivisonInfo*> m_vDivisionInfo; //0x06F0
    char pad_0700[0x28]; //0x0700
    HANDLE m_handle; //0x0728
};
