//
// Created by maximus on 4/9/2024.
//

#include "BSClientApp.h"

int CBSClientApp::LoadFileManager() {
    return reinterpret_cast<int (__thiscall *)(CBSClientApp *)>(0x0431F60)(this);
}

bool CBSClientApp::ValidateProcess() {
    return reinterpret_cast<int (__thiscall *)(CBSClientApp *)>(0x0431B70)(this);
}

void CBSClientApp::ReleaseFileManager() {
    reinterpret_cast<void (__thiscall *)(CBSClientApp *)>(0x0431B20)(this);
}
