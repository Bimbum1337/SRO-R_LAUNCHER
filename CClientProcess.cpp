//
// Created by maximus on 4/11/2024.
//

#include "CClientProcess.h"

int CClientProcess::OnReceiveMessage(CMsg &msg, int a2) {

    int nCurrentReadPos = msg.GetReadPos();

    printf("[S->C] - [0x%04X]\n\r", msg.GetMsgId());

    while (msg.GetReadPos() != msg.GetAvailableBytesForReading()) {
        BYTE bt;
        msg >> bt;

        printf("%02X ", bt);
    }

    printf("\n\r");
    msg.SetReadPos(nCurrentReadPos);


    return reinterpret_cast<int (__thiscall *)(CClientProcess *, CMsg&, int)>(0x040A880)(this, msg, a2);
}
