#include "NetEngine.h"
#include "Msg.h"

IBSNet::BSNET_ERR CNetEngine::OnSendMessage_IMPL(DWORD dwSessionID, CMsg *pMsg) {

    printf("[C->S] - [0x%04X]\n\r", pMsg->GetMsgId());

    int nCurrentReadPos = pMsg->GetReadPos();
    while (pMsg->GetReadPos() != pMsg->GetAvailableBytesForReading()) {
        BYTE bt;
        *pMsg >> bt;

        printf("%02X ", bt);
    }

    printf("\n\r");
    pMsg->SetReadPos(nCurrentReadPos);

    return reinterpret_cast<IBSNet::BSNET_ERR (__stdcall *)(CNetEngine *, DWORD, CMsg*)>(0x041A820)(this, dwSessionID, pMsg);
}
