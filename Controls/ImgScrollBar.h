//
// Created by maximus on 4/9/2024.
//

#pragma once

#include <../Lib.h>

class CImgScrollBar : public CWnd{
public:
    /// \address 0x00445B30
    void Init(CWnd* pParent, int nWidth, int nHeight, int nId, const char* strUp, const char* strMove, const char* strDown, const char* strBack);
};


