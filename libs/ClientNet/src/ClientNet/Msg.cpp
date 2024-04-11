//
// Created by Kurama on 12/25/2022.
//
#include <exception>
#include "Msg.h"

// todo : need to use the jmx exception

void CMsg::AddSizeToMsg(WORD wSize) {
    if (wSize > (~(-MSG_ENC_MASK)))
        throw std::exception("Ooops");

    // Lets Enc it back
    *m_wpMsgSize = (wSize | (*m_wpMsgSize & MSG_ENC_MASK));
}

void CMsg::ReadBytes(void *pOut, size_t cbSize) {
    if ((m_wReadDataArrayPos + cbSize) > m_wWriteDataArrayPos)
        throw std::exception("Ooops");

    memcpy(pOut, &m_pMsgBuffer[m_wReadDataArrayPos], cbSize);
    m_wReadDataArrayPos += cbSize;
}

void CMsg::ReadBytesReverse(const void *pOut, size_t cbSize) {
    if ((m_wWriteDataArrayPos - MSG_HEADER_SIZE) < cbSize)
        throw std::exception("Ooops");

    m_wWriteDataArrayPos -= cbSize;
    pOut = &m_pMsgBuffer[m_wWriteDataArrayPos];

    AddSizeToMsg((m_wWriteDataArrayPos - MSG_HEADER_SIZE));
}

void CMsg::WriteBytes(const void *pIn, size_t cbSize) {
    if (m_wWriteDataArrayPos + cbSize > m_dwArrayDataSize) {
        pIn = NULL;
        return;
    }

    memcpy(&m_pMsgBuffer[m_wWriteDataArrayPos], pIn, cbSize);
    m_wWriteDataArrayPos += cbSize;
    AddSizeToMsg((m_wWriteDataArrayPos - MSG_HEADER_SIZE));

}

void CMsg::WriteString(const char *pChar) {
    size_t cbLength = 0;

    if (pChar != NULL)
        cbLength = ::lstrlenA(pChar);

    if ((m_wWriteDataArrayPos + cbLength) >= m_dwArrayDataSize)
        cbLength = (m_dwArrayDataSize - m_wWriteDataArrayPos) - sizeof(char);

    (*this) << (WORD) cbLength;
    if (cbLength != 0)
        WriteBytes(pChar, cbLength);
}

void CMsg::WriteString(const std::string &str) {
    size_t cbLength = str.length();

    if ((m_wWriteDataArrayPos + cbLength) >= m_dwArrayDataSize)
        cbLength = (m_dwArrayDataSize - m_wWriteDataArrayPos) - sizeof(char);

    (*this) << (WORD) cbLength;
    if (cbLength != 0)
        WriteBytes(str.c_str(), cbLength);
}

void CMsg::ReadString(std::string &str) {
    short sLength = 0;
    (*this) >> sLength;

    str.resize(sLength);
    ReadBytes(&str[0], sLength);
}

void CMsg::ReadWString(std::wstring &str) {
    short sLength = 0;
    (*this) >> sLength;

    str.resize(sLength);
    ReadBytes(&str[0], sLength * 2);
}

void CMsg::WriteWString(const wchar_t *pChar) {
    size_t cbLength = 0;

    if (pChar != NULL)
        cbLength = ::lstrlenW(pChar);

    if ((m_wWriteDataArrayPos + cbLength) >= m_dwArrayDataSize)
        cbLength = (m_dwArrayDataSize - m_wWriteDataArrayPos) - sizeof(char);

    (*this) << (WORD) cbLength;

    if (cbLength != 0)
        WriteBytes(pChar, cbLength * 2);
}

void CMsg::WriteWString(const std::wstring &str) {
    size_t cbLength = str.length();

    if ((m_wWriteDataArrayPos + cbLength) >= m_dwArrayDataSize)
        cbLength = (m_dwArrayDataSize - m_wWriteDataArrayPos) - sizeof(char);

    (*this) << (WORD) cbLength;

    if (cbLength != 0)
        WriteBytes(str.c_str(), cbLength * 2);
}
