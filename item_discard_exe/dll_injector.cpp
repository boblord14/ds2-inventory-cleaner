//
// Created by false on 6/2/2024.
//
#include <string>
#include <iostream>
#include "dll_injector.h"

HANDLE dll_injector::GetRemoteProcessHandleA(char *pszProcessName) {
    HANDLE tlh = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

    PROCESSENTRY32 proEntry;

    proEntry.dwSize = sizeof( PROCESSENTRY32 );

    Process32First( tlh, &proEntry );
    do
    {
        if( _stricmp( pszProcessName, proEntry.szExeFile ) == 0 )
        {
            CloseHandle( tlh );

            return OpenProcess( PROCESS_ALL_ACCESS, FALSE, proEntry.th32ProcessID );
        }
    }
    while( Process32Next( tlh, &proEntry ) );

    CloseHandle( tlh );

    return INVALID_HANDLE_VALUE;
}

dll_injector::dll_injector(char *moduleName) {
    this->processHandle = GetRemoteProcessHandleA(moduleName);

    this->loadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandle(std::string("kernel32.dll").c_str()), "LoadLibraryA");

    if(loadLibraryAddr == nullptr) {
        std::cout << "Could not find LoadLibraryA function\n Try again, and if it still doesn't work contact boblord for further troubleshooting" << std::endl;
    }

    allocAddr = nullptr;

}

void dll_injector::inject_dll(const char *dllFilePath) {
    allocAddr = (LPVOID)VirtualAllocEx(processHandle, nullptr, strlen(dllFilePath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if(allocAddr == nullptr) {
        std::cout << "Could not allocate new memory inside the exe\n Try again, and if it still doesn't work contact boblord for further troubleshooting" << std::endl;
        return;
    }

    if(WriteProcessMemory(processHandle, allocAddr, dllFilePath, strlen(dllFilePath), nullptr) == FALSE) {
        std::cout << "Could not write the dll file path inside the exe\n Try again, and if it still doesn't work contact boblord for further troubleshooting" << std::endl;
        return;
    }

}

dll_injector::~dll_injector() {
    CloseHandle(processHandle);
}

void dll_injector::execute_dll() {
    HANDLE createdThread = CreateRemoteThread(processHandle, nullptr, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, allocAddr, NULL, nullptr);

    if(createdThread == nullptr) {
        std::cout << "Could not execute remote dll inside the exe\n Try again, and if it still doesn't work contact boblord for further troubleshooting" << std::endl;
        return;
    }
}


