//
// Created by maximus on 4/9/2024.
//

#include "ImgStaticWnd.h"
#include "../BSClientDlg.h"

BEGIN_MESSAGE_MAP(CImgStaticWnd, CStatic)
                    ON_WM_PAINT()
END_MESSAGE_MAP()

// i will do it that way cause i would need to make something like a gif
void CImgStaticWnd::OnPaint() {
    CPaintDC dc(this);

    CRect rect;
    GetClientRect(&rect);

    CDC memDC;
    if (!memDC.CreateCompatibleDC(&dc)) {
        return;
    }

    if(!m_strImgPath.empty()) {
        CGdiObject gdiObject;

        if (!GetRegisteredFile(m_strImgPath.c_str(), &gdiObject)) {
            return;
        }

        CBitmap* pOldBitmap = dynamic_cast<CBitmap*>(memDC.SelectObject(&gdiObject));

        ::StretchBlt(dc.GetSafeHdc(), 0, 0, rect.right, rect.bottom,
                     memDC, 0, 0, rect.right, rect.bottom, SRCCOPY);


        memDC.SelectObject(pOldBitmap);
    }

    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(RGB(255, 255, 255));

    // Draw text
    CString strText;
    strText.Append(m_strText.c_str());
    dc.TextOut(0, 0, strText);

}

void CImgStaticWnd::SetData(std::string strText, std::string strImg) {
    m_strImgPath = strImg;

    m_strText = strText;
}
