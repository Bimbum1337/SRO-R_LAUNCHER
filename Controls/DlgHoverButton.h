//
// Created by maximus on 4/10/2024.
//

#pragma once

#include <../Lib.h>


class CDlgHoverButton : public CButton {
public:
    ///\address 0x444400
    CDlgHoverButton();
    ~CDlgHoverButton() {

    }

private:
    DECLARE_DYNAMIC(CDlgHoverButton)
    DECLARE_MESSAGE_MAP()

private:
    struct _SxSourceCoordinates {
        _SxSourceCoordinates() : width(0), height(0){

        }
        __int16 width;
        __int16 height;
    };

public:
    ///\address 0x00444070
    void SetImage(const char *lpStrImg, int nWidthOffset, int nHeightOffset, BYTE btCountOfRepeatedObjects);

private:
    ///\address 0x00443F60
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    ///\address 0x00444150
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    ///\address 0x00443F40
    afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);

    ///\address 0x004441A0
    afx_msg int OnMouseLeave(int, int);

    ///\address 0x004441C0
    afx_msg int OnMouseHover(int, int);

#if 0
    ///\address 0x00444200
    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); /// NO CLUE WHY ITS NOT BEING CALLED //TODO
#endif

///\ CUSTOM
    void OnPaint();

    void OnLButtonDown(UINT nFlags, CPoint point);

    void OnLButtonUp(UINT nFlags, CPoint point);
///\ CUSTOM

private:
    BYTE m_btRepeatedObjectsCount; //0x0054
    int m_bHovered; //0x0058
    HWND m_hWnd_eventHover; //0x005C
    RECT m_rect_img; //0x0060
    CBitmap m_bitMap_Img; //0x0070
    BITMAP m_bitMapGraphicInfo; //0x0078
    CBitmap m_bitMap_Img_2; //0x0090
    HCURSOR m_hCursor; //0x0098
    _SxSourceCoordinates m_originalCoordinates; //0x009C
    const char *m_lpStrText; //0x00A0
    //\ 0: NORMAL  1: HOVER  2: CLICK
    _SxSourceCoordinates m_sourceCoordinates[3]; //0x00A4

    ///\CUSTOM
    bool m_bClicked;
    ///\CUSTOM
};


