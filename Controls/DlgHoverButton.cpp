//
// Created by maximus on 4/10/2024.
//

#include "DlgHoverButton.h"
#include "../afxmsg_custom.h"
#include "../AfxStringMgr.h"
#include "../BSClientDlg.h"

IMPLEMENT_DYNAMIC(CDlgHoverButton, CButton)

BEGIN_MESSAGE_MAP(CDlgHoverButton, CButton)
                    ON_WM_PAINT()
                    ON_WM_CREATE()
                    ON_WM_MOUSEMOVE()
                    ON_WM_SETCURSOR()
                    ON_WM_MOUSEHOVER()
                    ON_WM_MOUSELEAVE()
                    ON_WM_LBUTTONDOWN()
                    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


CDlgHoverButton::CDlgHoverButton() {
    m_bHovered = FALSE;
    m_hWnd_eventHover = NULL;
    m_bClicked = false;
    m_lpStrText = static_cast<const char *>(CAfxStringMgr::Get()->GetNilString()->data());
}

void
CDlgHoverButton::SetImage(const char *lpStrImg, int nWidthOffset, int nHeightOffset, BYTE btCountOfRepeatedObjects) {
    m_btRepeatedObjectsCount = btCountOfRepeatedObjects;

    GetRegisteredFile(lpStrImg, &m_bitMap_Img);

    GetObjectA(m_bitMap_Img.m_hObject, 24, &m_bitMapGraphicInfo);

    int nSegmentsCount = 1;
    if (m_btRepeatedObjectsCount & 1) ++nSegmentsCount;
    if (m_btRepeatedObjectsCount & 2) ++nSegmentsCount;

    __int16 width = 0;
    __int16 height = 0;

    if (nHeightOffset) {
        height = m_bitMapGraphicInfo.bmHeight - nWidthOffset * (m_bitMapGraphicInfo.bmHeight / nHeightOffset);
        width = m_bitMapGraphicInfo.bmWidth / nSegmentsCount;
        m_originalCoordinates.height = m_bitMapGraphicInfo.bmHeight / nHeightOffset;
    } else {
        width = width = m_bitMapGraphicInfo.bmWidth / nSegmentsCount;
        m_originalCoordinates.height = m_bitMapGraphicInfo.bmHeight;
    }

    m_originalCoordinates.width = width;

    m_sourceCoordinates[0].width = 0;
    m_sourceCoordinates[0].height = height;

    if (m_btRepeatedObjectsCount & 1) {
        m_sourceCoordinates[1].width = width;
        m_sourceCoordinates[1].height = height;

        width *= 2;
    }

    if (m_btRepeatedObjectsCount & 2) {
        m_sourceCoordinates[2].width = width;
        m_sourceCoordinates[2].height = height;
    }

    //reinterpret_cast<void (__thiscall *)(CDlgHoverButton *, const char*, int, int, char)>(0x0444070)(this, lpStrImg, a3, a4, a5);
}

int CDlgHoverButton::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    return Default();
}

void CDlgHoverButton::OnMouseMove(UINT nFlags, CPoint point) {
    struct tagTRACKMOUSEEVENT EventTrack;

    if (!m_hWnd_eventHover) {
        EventTrack.cbSize = 16;
        EventTrack.hwndTrack = m_hWnd;
        EventTrack.dwFlags = 3;
        EventTrack.dwHoverTime = 1;
        m_hWnd_eventHover = reinterpret_cast<HWND>(TrackMouseEvent(&EventTrack));
    }

    Default();
}

BOOL CDlgHoverButton::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message) {
    ::SetCursor(m_hCursor);

    return TRUE;
}

int CDlgHoverButton::OnMouseLeave(int, int) {
    m_bHovered = FALSE;
    m_hWnd_eventHover = NULL;

    ::InvalidateRect(m_hWnd, NULL, NULL);

    return 0;
}

int CDlgHoverButton::OnMouseHover(int, int) {
    m_bHovered = TRUE;

    ::InvalidateRect(m_hWnd, NULL, NULL);

    return 0;
}

#if 0
void CDlgHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    pDC->SetBkMode(TRANSPARENT);

    ::GetClientRect(m_hWnd, &m_rect_img);

    CDC memDC;
    HDC dc = CreateCompatibleDC(pDC->m_hDC);

    memDC.Attach(dc);

    SetBkMode(dc, TRANSPARENT);

    _SxSourceCoordinates sourceCoordinates = m_sourceCoordinates[0];

    if (lpDrawItemStruct->itemState & 1 && m_btRepeatedObjectsCount & 2) {
        sourceCoordinates = m_sourceCoordinates[2];
    } else if (m_bHovered == TRUE && m_btRepeatedObjectsCount & 1) {
        sourceCoordinates = m_sourceCoordinates[1];
    }

    HBITMAP hOldBitmap = (HBITMAP) SelectObject(dc, m_bitMap_Img);

    BitBlt(pDC->m_hDC, 0, 0, m_rect_img.right, m_rect_img.bottom,
           dc, sourceCoordinates.width, sourceCoordinates.height, SRCCOPY);

    if (m_btRepeatedObjectsCount & 4) {
        tagTEXTMETRICA tagTEXTMETRICA;
        GetTextMetricsA(pDC->m_hDC, &tagTEXTMETRICA);

        RECT rectText = {m_rect_img.left, (m_rect_img.bottom - tagTEXTMETRICA.tmHeight) / 2 + m_rect_img.top,
                     m_rect_img.right, (m_rect_img.bottom - tagTEXTMETRICA.tmHeight) / 2 + tagTEXTMETRICA.tmHeight};

        DrawTextA(pDC->m_hDC, m_lpStrText, strlen(m_lpStrText), &rectText, 1);
    }

    SelectObject(dc, hOldBitmap);
    DeleteDC(dc);
}
#endif

void CDlgHoverButton::OnPaint()
{
    CPaintDC pDC(this);
    pDC.SetBkMode(TRANSPARENT);

    CRect rectClient;
    GetClientRect(&rectClient);

    CDC memDC;
    memDC.CreateCompatibleDC(&pDC);

    HBITMAP hOldBitmap = (HBITMAP)memDC.SelectObject(m_bitMap_Img);

    _SxSourceCoordinates sourceCoordinates = m_sourceCoordinates[0];

    if(m_bClicked == TRUE) {
        sourceCoordinates = m_sourceCoordinates[2];
    } else if (m_bHovered == TRUE) {
        sourceCoordinates = m_sourceCoordinates[1];
    }

    pDC.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
               &memDC, sourceCoordinates.width, sourceCoordinates.height, SRCCOPY);


    if (m_btRepeatedObjectsCount & 4)
    {
        TEXTMETRIC tm;
        pDC.GetTextMetrics(&tm);

        CRect rectText(rectClient.left, (rectClient.bottom - tm.tmHeight) / 2,
                       rectClient.right, (rectClient.bottom + tm.tmHeight) / 2);

        DrawTextA(pDC.m_hDC, m_lpStrText, strlen(m_lpStrText), &rectText, 1);
    }

    memDC.SelectObject(hOldBitmap);
}

void CDlgHoverButton::OnLButtonDown(UINT nFlags, CPoint point) {
    m_bClicked = true;

    CWnd::OnLButtonDown(nFlags, point);

    ::InvalidateRect(m_hWnd, NULL, NULL);
}

void CDlgHoverButton::OnLButtonUp(UINT nFlags, CPoint point) {
    m_bClicked = false;

    CWnd::OnLButtonUp(nFlags, point);

    ::InvalidateRect(m_hWnd, NULL, NULL);

    MessageBox("Hey", "Bimbum");
}





