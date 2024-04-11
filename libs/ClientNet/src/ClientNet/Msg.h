#pragma once

#include <string>
#include "Windows.h"

enum MSG_READ_MODE : DWORD {
    MSG_READ_MODE_REVERSE,
    MSG_READ_MODE_NORMAL,
};

// Msg Info
#define MSG_BUFFER_SIZE 4096

#define MSG_BUFFER_OFFSET 0

#define MSG_SIZE_OFFSET MSG_BUFFER_OFFSET
#define MSG_ID_OFFSET (MSG_SIZE_OFFSET + sizeof(WORD)) // 2
#define MSG_SEQ_OFFSET (MSG_ID_OFFSET + sizeof(WORD))
#define MSG_CRC_OFFSET (MSG_SEQ_OFFSET + sizeof(BYTE))

#define MSG_DATA_OFFSET (MSG_CRC_OFFSET + sizeof(BYTE)) // 6
#define MSG_ENC_DATA_OFFSET (MSG_BUFFER_OFFSET + sizeof(WORD))

#define MSG_HEADER_SIZE MSG_DATA_OFFSET
#define MSG_DATA_SIZE MSG_BUFFER_SIZE - MSG_HEADER_SIZE;

#define MSG_ENC_MASK (WORD)0x8000

#define READ_FROM_EXISTING_MSG     int nCurrentReadPos = msg.GetReadPos();
#define END_READING     msg.SetReadPos(nCurrentReadPos);

class CMsg {
    // non vtable
public:
    template<typename T>
    CMsg &operator>>(T &pOut) {
        ReadBytes(pOut);
        return *this;
    }

    CMsg &operator>>(std::string &str) {
        ReadString(str);
        return *this;
    }

    CMsg &operator>>(std::wstring &str) {
        ReadWString(str);
        return *this;
    }

    template<typename T>
    CMsg &operator<<(T In) {
        WriteBytes(&In, sizeof(T));
        return *this;
    }

    CMsg &operator<<(LPCSTR str) {
        WriteString(str);
        return *this;
    }

    CMsg &operator<<(const std::string &str) {
        WriteString(str);
        return *this;
    }

    CMsg &operator<<(LPCWSTR str) {
        WriteWString(str);
        return *this;
    }

    CMsg &operator<<(const std::wstring &str) {
        WriteWString(str);
        return *this;
    }

private:
    template<typename T>
    void ReadBytesEx(T &pOut) {
        ReadBytes(&pOut, sizeof(T));
    }

    template<typename T>
    void ReadBytesReverseEx(T &pOut) {
        ReadBytesReverse(&pOut, sizeof(T));
    }

    template<typename T>
    void ReadBytes(T &pOut) {
        if (m_dwReadMsgMode == MSG_READ_MODE_REVERSE)
            ReadBytesReverseEx(pOut);
        else
            ReadBytesEx(pOut);
    }

public:
    void SetMsgID(WORD wMsgID) { *m_wpMsgId = wMsgID; }

    WORD GetMsgId() const { return *m_wpMsgId; }

    DWORD GetSessionId() const { return m_dwSessionID; }

    void SetReadPos(WORD wPos) { m_wReadDataArrayPos = wPos; }

    WORD GetReadPos() const { return m_wReadDataArrayPos; }

    WORD GetAvailableBytesForReading() const { return m_wWriteDataArrayPos; }

    void FlushRemainingBytes() { m_wReadDataArrayPos = m_wWriteDataArrayPos; }

    void ReadBytes(void *pOut, size_t cbSize);

    void ReadBytesReverse(const void *pOut, size_t cbSize);

    void WriteBytes(const void *pIn, size_t cbSize);

    void WriteString(const char *pChar);

    void WriteString(const std::string &str);

    void ReadString(std::string &str);

    void ReadWString(std::wstring &str);

    void WriteWString(const wchar_t *pChar);

    void WriteWString(const std::wstring &str);

    void AddSizeToMsg(WORD wSize);

public:
    char pad_0000[0x28]; //0x0000
    char *m_pOldMsgBuffer; //0x0028
    char pad_002c[8]; //0x002c
    char m_MsgBuffer[MSG_BUFFER_SIZE]; //0x0034
    char *m_pMsgBuffer; //0x1034
    char *m_pMsgBufferEx; //0x1038 if the m_pMsgBuffer array size is bigger than m_dwArrayDataSize this mem get allocate
    WORD m_wReadDataArrayPos; //0x103c
    WORD m_wWriteDataArrayPos; //0x103e
    char pad_1040[4]; //0x1040
    int m_cMsgUsage; //0x1044
    MSG_READ_MODE m_dwReadMsgMode; //0x1048
    DWORD m_dwArrayDataSize; //0x104c
    WORD *m_wpMsgId; //0x1050
    WORD *m_wpMsgSize; //0x1054
    BYTE *m_bpSequence; //0x1058
    BYTE *m_bpCRC; //0x105C
    DWORD m_dwSessionID; //0x1060
    char pad_1064[4]; //0x1064
    LONG m_lIsAllocated; //0x1068 0 mean freed 1 mean still can use
    char pad_106c[14]; //0x106c

};