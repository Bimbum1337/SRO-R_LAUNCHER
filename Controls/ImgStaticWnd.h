//
// Created by maximus on 4/9/2024.
//


#include <../Lib.h>

class CImgStaticWnd : public CStatic {
private:
    DECLARE_MESSAGE_MAP()

private:
    void OnPaint();

public:
    void SetData(std::string strText, std::string strImg);

private:
    std::string m_strText;
    std::string m_strImgPath;
};


