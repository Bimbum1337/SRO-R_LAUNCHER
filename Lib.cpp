//
// Created by maximus on 4/7/2024.
//

#include <cstdio>
#include "Lib.h"
#include "hook.h"
#include "BSClientDlg.h"

void Setup() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);

    ///\ Load files
    placeHook(0x004392D0, addr_from_this(&CBSClientDlg::InitFiles));

    ///\ On Create Windows
    vftableHook(0x0049FC1C, 82, addr_from_this(&CBSClientDlg::OnInitDialog_IMPL));

    ///\ Data exchance
    vftableHook(0x0049FC1C, 61, addr_from_this(&CBSClientDlg::DoDataExchange_IMPL));
}