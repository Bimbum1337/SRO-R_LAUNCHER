//
// Created by maximus on 4/9/2024.
//

#include "BSClientDlg.h"
#include "BSClientApp.h"
#include "TextStringManager.h"
#include "DivisonManager.h"
#include "ImgStaticWnd.h"

enum {
    IDR_HTML_DIALOG = 199,
};
int GetRegisteredFile(const char *fileName, CGdiObject *pObj) {
    return reinterpret_cast<int (__cdecl *)(const char *fileName, CGdiObject *pObj)>(0x04367B0)(fileName, pObj);
}

int RegisterFile(const char *fileName, int nStatic) {
    return reinterpret_cast<int (__cdecl *)(const char *, int)>(0x04385C0)(fileName, nStatic);
}

int CBSClientDlg::InitFiles() {
    RegisterFile("\\Launcher\\homepage_1.dat", 1);
    RegisterFile("\\Launcher_Europe\\bg_4.dat", 1);
    RegisterFile("\\Launcher_Europe\\bg_5.dat", 1);
    RegisterFile("\\Launcher_Europe\\bg_4.dat", 1);
    RegisterFile("\\Launcher_Europe\\bg_5.dat", 1);
    RegisterFile("\\Launcher_Europe\\bg_division_4.dat", 1);
    RegisterFile("\\Launcher_Europe\\bg_division_5.dat", 1);
    RegisterFile("\\Launcher\\update_focus.dat", 1);
    RegisterFile("\\Launcher\\update_select.dat", 1);
    RegisterFile("\\Launcher\\bitmap_g.dat", 1);
    RegisterFile("\\Launcher\\config_bright.dat", 1);
    RegisterFile("\\Launcher\\config_graphic.dat", 1);
    RegisterFile("\\Launcher\\config_resolution.dat", 1);
    RegisterFile("\\Launcher\\division_1.dat", 1);
    RegisterFile("\\Launcher\\division_2.dat", 1);
    RegisterFile("\\Launcher\\division_3.dat", 1);
    RegisterFile("\\Launcher\\division_select.dat", 1);
    RegisterFile("\\Launcher\\exit.dat", 1);
    RegisterFile("\\Launcher\\gauge_back.dat", 1);
    RegisterFile("\\Launcher\\gauge.dat", 1);
    RegisterFile("\\Launcher\\guide.dat", 1);
    RegisterFile("\\Launcher\\ok.dat", 1);
    RegisterFile("\\Launcher\\left.dat", 1);
    RegisterFile("\\Launcher\\movie.dat", 1);
    RegisterFile("\\Launcher\\option.dat", 1);
    RegisterFile("\\Launcher\\patch.dat", 1);
    RegisterFile("\\Launcher\\right.dat", 1);
    RegisterFile("\\Launcher\\scroll_back.dat", 1);
    RegisterFile("\\Launcher\\scroll_back_02.dat", 1);
    RegisterFile("\\Launcher\\scroll_down.dat", 1);
    RegisterFile("\\Launcher\\scroll_move.dat", 1);
    RegisterFile("\\Launcher\\scroll_up.dat", 1);
    RegisterFile("\\Launcher\\soundbox.dat", 1);
    RegisterFile("\\Launcher\\start.dat", 1);
    RegisterFile("\\Launcher\\window_close.dat", 1);
    RegisterFile("\\Launcher\\window_option.dat", 1);
    RegisterFile("\\Launcher\\window_update.dat", 1);

    ///\ I believe that 0 means the file will be rendered as source file (StretchBlt)
    RegisterFile("\\Launcher\\LauncherReview.dat", 0);
    RegisterFile("\\Launcher\\config_box_02.dat", 0);
    RegisterFile("\\Launcher\\new_scroll_down.dat", 0);

    RegisterFile("\\Launcher\\scroll_back_03.dat", 1);
    RegisterFile("\\Launcher\\sf_language_button.dat", 1);
    RegisterFile("\\Launcher\\sf_language_select_frame_top.dat", 1);
    RegisterFile("\\Launcher\\sf_language_select_frame_mid.dat", 1);
    RegisterFile("\\Launcher\\sf_language_select_frame_bottom.dat", 1);
    RegisterFile("\\Launcher\\com_Mid_button_ok.dat", 1);
    RegisterFile("\\Launcher\\com_Mid_button_cancel.dat", 1);
    RegisterFile("\\Launcher\\sf_radiobutton.dat", 1);
    RegisterFile("\\Launcher\\sf_language_big_no_img.dat", 1);

    return 1;
}

BOOL CBSClientDlg::OnInitDialog_IMPL() {
   BOOL bResult = reinterpret_cast<BOOL (__thiscall *)(CBSClientDlg *)>(0x43A530)(this);

   AfterInitDialog();

   return bResult;

    try {
        OnInitDialog();
        ::SendMessageA(m_hWnd, 0x80, 1, (LPARAM) m_dcHwnd);
        ::SendMessageA(m_hWnd, 0x80, 0, (LPARAM) m_dcHwnd);

        HANDLE hHandle = CreateMutexA(NULL, NULL, "Silkroad Client");
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            MessageBox("Silkroad Online", "Silkroad is already executed!!");
            exit(0);
        }
        CloseHandle(hHandle);

        m_handle = CreateMutexA(NULL, NULL, "Silkroad Online Launcher");
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            MessageBox("Silkroad Online", "Silkroad is already executed!!");
            exit(0);
        }

        CBSClientDlg::InitPath();

        if (!g_cBSClientApp.LoadFileManager()) {
            MessageBox("Silkroad Online", "Failed To Initialize FileManager.");
            exit(0);
        }

        InitFiles();

        if (!CBSClientDlg::VerifyConnection()) {
            MessageBox("Silkroad Online", TSM_GETTEXTPTR("UILM_MSG_FAILED_LOAD_CLIENT"));
            exit(0);
        }

        CreateChildControls();

        RegisterDivisonKey();

        if (!g_cBSClientApp.ValidateProcess()) {
            MessageBox("Silkroad Online", "Detected Abnormal Process..(System Error)");
            exit(0);
        }

        char buf[127];
        sprintf_s(buf, "%s Launcher", "Silkroad Online");
        SetWindowTextA(buf);

        RECT rtMainWindow;
        GET_CLIENT_RECT(rtMainWindow, 1);

        MoveWindow(rtMainWindow.left, rtMainWindow.top, rtMainWindow.right, rtMainWindow.bottom, 1);

        ::GetClientRect(m_hWnd, &m_articleRect[0]);

        RECT rtHTMLWindow;
        GET_CLIENT_RECT(rtHTMLWindow, 13);

        if (rtHTMLWindow.left > 0 ||
            rtHTMLWindow.top > 0 || rtHTMLWindow.right > 0 || rtHTMLWindow.bottom > 0) {
            if(m_pHtmlDialog) return 0;

            m_pHtmlDialog = new CDHtmlDialog();
            m_pHtmlDialog->Create(IDR_HTML_DIALOG, this);

            RECT rt;
            SetRect(&rt, rtHTMLWindow.left, rtHTMLWindow.top, rtHTMLWindow.right + m_articleRect[0].right, rtHTMLWindow.bottom + m_articleRect[0].bottom);

            m_pHtmlDialog->MoveWindow(rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, 1);
        }

        SetBackGroundImages();

        CreateDefaultFont();

        if(LANGUAGE == GLOBAL) {
            LoadGlobalLang();
            InitGlobalLangImage();
        }

        g_cBSClientApp.ReleaseFileManager();

        if(m_vDivisionInfo.size() == 1) {
            g_btDivision = 0;

            g_pDivisionManager->ControlDivisionWindow();

            StartGatewayService();
        } else {
            g_btDivision = -1;

            g_pDivisionManager->ShowDivisionWindow();
        }

        if(LANGUAGE == KOREA) {
            ShowLanguangeSelectWindow();

            ::SetTimer(m_hWnd, 191, 3600000, 0);
        }

        if(m_pHtmlDialog) {
            m_pHtmlDialog->ShowWindow(5);
            m_pHtmlDialog->InvalidateRect(NULL, 1);
        }

        RECT rtArticleScroll;
        GET_CLIENT_RECT(rtArticleScroll, 4);

        const char* strLauncherScroll[4] = {"\\Launcher\\scroll_up.dat", "\\Launcher\\scroll_move.dat","\\Launcher\\scroll_down.dat","\\Launcher\\scroll_back_03.dat"};

        m_pArticleScroll.Init(this, 204, 734, 73, strLauncherScroll[0], strLauncherScroll[1], strLauncherScroll[2], strLauncherScroll[3]);
        m_pArticleScroll.ShowWindow(false);


        RECT rtArticleHeadLine;
        GET_CLIENT_RECT(rtArticleHeadLine, 5);
        SetRect(&m_articleRect[1], rtArticleHeadLine.left, rtArticleHeadLine.top, rtArticleHeadLine.left + rtArticleHeadLine.right, rtArticleHeadLine.bottom + 1 + rtArticleHeadLine.top + 2 * (rtArticleHeadLine.bottom + 1));

        rtArticleScroll.right = rtArticleHeadLine.right;
        rtArticleScroll.bottom = rtArticleHeadLine.bottom;

        RECT rtArticleViewer;
        GET_CLIENT_RECT(rtArticleViewer, 3);
        SetRect(&m_articleRect[2], rtArticleViewer.left, rtArticleViewer.top, rtArticleViewer.left + rtArticleViewer.right, rtArticleViewer.top + rtArticleViewer.bottom);

    } catch (...) {
        printf("WTFFFFFF %s\n\r", __FUNCTION__);
    }

    return 1;
#if 0
    BOOL bResult = reinterpret_cast<BOOL (__thiscall *)(CBSClientDlg *)>(0x43A530)(this);


    return bResult;
#endif
}

void CBSClientDlg::InitPath() {
    reinterpret_cast<void (*)()>(0x0432720)();
}

bool CBSClientDlg::VerifyConnection() {
    return reinterpret_cast<bool (__thiscall *)(CBSClientDlg *)>(0x043A0E0)(this);
}

void CBSClientDlg::CreateChildControls() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x433DD0)(this);
}

void CBSClientDlg::RegisterDivisonKey() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x04355A0)(this);
}

void CBSClientDlg::SetBackGroundImages() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x4375B0)(this);
}

void CBSClientDlg::CreateDefaultFont() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x434E60)(this);
}

void CBSClientDlg::LoadGlobalLang() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x438EC0)(this);
}

void CBSClientDlg::InitGlobalLangImage() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x438990)(this);
}

void CBSClientDlg::StartGatewayService() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x439580)(this);
}

void CBSClientDlg::ShowLanguangeSelectWindow() {
    reinterpret_cast<void (__thiscall *)(CBSClientDlg *)>(0x433590)(this);
}

void CBSClientDlg::AfterInitDialog() {
    //CREATE YOUR CONTROLS

    CImgStaticWnd* pImgStaticWnd = new CImgStaticWnd();

    pImgStaticWnd->Create("", WS_CHILD | WS_VISIBLE, CRect(50, 10, 100,  20),  this, 1337);
    pImgStaticWnd->SetData("Bimbular", "");
}
