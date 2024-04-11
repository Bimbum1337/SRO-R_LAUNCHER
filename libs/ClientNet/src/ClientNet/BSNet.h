//
// Created by Kurama on 2/15/2023.
//
#pragma once

// sorry
#include "Windows.h"
#include <string>

struct IUnknownInterface {
};

struct IBSNet : public IUnknownInterface {
    enum BSNET_ERR : DWORD {
        BSNET_ERR_PEER_DOESNT_RESPONSE = 32789,
        BSNET_ERR_FAILED_TO_CREATE_SESSION = 32788,
        BSNET_ERR_TARGET_TASK_LOST = 32787,
        BSNET_ERR_COMPLETION_TARGET_MISMATCH = 32786,
        BSNET_ERR_INVALID_MSG_HEADER = 32785,
        BSNET_ERR_NET_ACCESSED_BEFORE_HANDSHAKE = 32784,
        BSNET_ERR_INVALID_TARGET_FILE = 32783,
        BSNET_ERR_FAILED_TO_ACCEPT = 32782,
        BSNET_ERR_INVALID_MSGSIZE = 32781,
        BSNET_ERR_INVALID_CHECKSUM = 32780,
        BSNET_ERR_INVALID_SEQUENCE = 32779,
        BSNET_ERR_FAILED_TO_TRANSFILE = 32778,
        BSNET_ERR_INVALID_SESSION = 32777,
        BSNET_ERR_INVALID_SOCKET = 32776,
        BSNET_ERR_NO_MSGTARGET = 32775,
        BSNET_ERR_NODATA_TO_SEND = 32774,
        BSNET_ERR_TOO_MANY_OUTSTANDING = 32773,
        BSNET_ERR_BUFFER_FULL = 32772,
        BSNET_ERR_SESSION_LOST = 32771,
        BSNET_ERR_UNKNOWN = 32770,
        BSNET_ERR_TIMEOUT = 32769,
        BSNET_ERR_OK = 0,
    };

public:
private:
    // size is 0x114?
};