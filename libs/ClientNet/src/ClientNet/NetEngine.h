//
// Created by Kurama on 2/15/2023.
//
#pragma once

#include "BSNet.h"

class CMsg;

class CNetEngine : public IBSNet {
public:
    virtual void __stdcall Func_0();

    virtual void __stdcall Func_1();

    // CNetEngine::Release
    virtual bool __stdcall Release();

    virtual void __stdcall Func_3();

    virtual void __stdcall Func_4();

    virtual void __stdcall Func_5();

    virtual void __stdcall Func_6();

    virtual void __stdcall Func_7();

    virtual void __stdcall Func_8();

    virtual void __stdcall Func_9();

    virtual void __stdcall Func_10();

    virtual void __stdcall Func_11();

    virtual void __stdcall Func_12();

    virtual void __stdcall Func_13();

    virtual void __stdcall Func_14();

    virtual void __stdcall Func_15();

    virtual void __stdcall Func_16();

    virtual void __stdcall Func_17();

    virtual CMsg *__stdcall AllocNewMsg(bool bEncode);

    virtual void __stdcall FreeMsg(CMsg *pMsg);

    virtual BSNET_ERR __stdcall SendMsg(DWORD dwSessionID, CMsg *pMsg);

    virtual void __stdcall Func_21();

    virtual void __stdcall Func_22();

    virtual bool __stdcall RecvFile(DWORD dwSessionID, std::string *pPath, DWORD dwOffset, int a5);

    virtual bool __stdcall SendFile(DWORD dwSessionID, std::string *pPath, DWORD dwOffset, int a5);

    virtual void __stdcall Disconnect(DWORD dwSessionID, DWORD dwReason);

    virtual void __stdcall Func_26();

    virtual void __stdcall Func_27();

    virtual void __stdcall Func_28();

    virtual void __stdcall Func_29();

    virtual void __stdcall Func_30();

    virtual void __stdcall Func_31();

    virtual void __stdcall Func_32();

    virtual void __stdcall Func_33();

    virtual void __stdcall Func_34();

    virtual void __stdcall Func_35();

    virtual void __stdcall Func_36();

    virtual void __stdcall Func_37();

    virtual void __stdcall Func_38();

    virtual void __stdcall Func_39();

    virtual ~CNetEngine();

public:
    BSNET_ERR __stdcall OnSendMessage_IMPL(DWORD dwSessionID, CMsg *pMsg);
#ifndef CLIENT_BUILD
    virtual void RegisterMaxConnections(int, int);
#endif // CLIENT_BUILD
private:
    // Unknown size

public:
    void SendMsgToShardManager(CMsg* pMsg);
};

#define g_pNetEngine (*((CNetEngine**)0x004D9F54))
