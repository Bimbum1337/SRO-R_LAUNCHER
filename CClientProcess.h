//
// Created by maximus on 4/11/2024.
//

#include "ClientNet/Msg.h"

class CBase {
};

class CServiceObject : public CBase {

};

class CClientProcess : public CServiceObject {
public:
    int OnReceiveMessage(CMsg &msg, int a2);
};


