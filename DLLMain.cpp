//
// Created by maximus on 4/7/2024.
//

#include "Lib.h"

extern "C" _declspec(dllexport)

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        Setup();
    }
    return TRUE;
}