//
// Created by maximus on 4/9/2024.
//

#pragma once

#include "SingletonT.h"
#include "Controls/DivisionWindow.h"
#include "BSClientDlg.h"

class CDivisionManager : public CSingletonT<CDivisionManager> {
public:
    virtual ~CDivisionManager() = 0;

public:
    /// \address 00456AB0
    void ControlDivisionWindow();

    /// \address 00456A70
    void ShowDivisionWindow();

public:
    CBSClientDlg *g_pBSClientDlg;
    CDivisionWindow *m_pDivisionWindow;
};


#define g_pDivisionManager (*((CDivisionManager**)0x004C615C))
