//
// Created by false on 6/2/2024.
//

#ifndef DS2_INVENTORY_CLEANER_DLL_INJECTOR_H
#define DS2_INVENTORY_CLEANER_DLL_INJECTOR_H

#include <Windows.h>
#include <vector>
#include <TlHelp32.h>

class dll_injector{
private:
    HANDLE processHandle;
    LPVOID loadLibraryAddr;
    LPVOID allocAddr;
    static HANDLE GetRemoteProcessHandleA( char *pszProcessName );
public:
    dll_injector(char* moduleName);
    ~dll_injector();
    void inject_dll(const char* dllFilePath);
    void execute_dll();
};

#endif //DS2_INVENTORY_CLEANER_DLL_INJECTOR_H
