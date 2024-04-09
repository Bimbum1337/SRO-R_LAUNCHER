//
// Created by maximus on 4/9/2024.
//

#include "ImgScrollBar.h"

void CImgScrollBar::Init(CWnd *pParent, int nWidth, int nHeight, int nId, const char* strUp, const char*strMove,
                         const char*strDown, const char* strBack) {
    reinterpret_cast<void (__thiscall *)(CImgScrollBar *, CWnd *, int, int, int, const char*, const char*,
                                         const char*, const char*)>(0x0445B30)
            (this, pParent, nWidth, nHeight, nId, strUp, strMove, strDown, strBack);
}
