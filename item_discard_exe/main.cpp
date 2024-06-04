#include <iostream>
#include "dll_injector.h"
#include <string>
#include <fstream>
#include <filesystem>

std::string WStringToString(const std::wstring& wstr)
{
    std::string str;
    size_t size;
    str.resize(wstr.length());
    wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
    return str;
}

std::string ExePath() {
    wchar_t buffer[MAX_PATH] = { 0 };
    GetModuleFileNameW( nullptr, buffer, MAX_PATH );
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return WStringToString(std::wstring(buffer).substr(0, pos));
}

std::filesystem::path writeDllFromResource(LPVOID resourcePtr, DWORD resourceSize){
    wchar_t buffer[MAX_PATH] = { 0 };
    GetTempPathW(MAX_PATH, buffer);
    std::string tempFolderPath = WStringToString(buffer) + "ds2itemdiscard";
    std::filesystem::create_directory(tempFolderPath);

    std::filesystem::path dllPath = tempFolderPath + "\\discardItems.dll";
    std::ofstream dllFile(dllPath, std::ofstream::binary | std::ofstream::out);
    dllFile.write(reinterpret_cast<char*>(resourcePtr), resourceSize);
    dllFile.close();
    return dllPath;
}

std::filesystem::path extractDll(){
    HRSRC informationBlockHandle = FindResourceA(nullptr, "DISCARDITEMS", RT_RCDATA);
    HGLOBAL resourceHandle = LoadResource(nullptr, informationBlockHandle);
    LPVOID resourcePtr = LockResource(resourceHandle);
    DWORD resourceSize = SizeofResource(nullptr, informationBlockHandle);
    if(resourcePtr != nullptr){
        return writeDllFromResource(resourcePtr, resourceSize);
    }else{
        std::cout << "could not find resource. make sure discardItems.dll is properly packed" << std::endl;
    }
    return {};
}



int main() {
    std::cout << "Boblord's Dark Souls 2 Inventory Cleaner" << std::endl;
    std::cout << "Works on the latest version of Scholar of the First Sin only(v1.03)\n" << std::endl;
    std::cout << "Removes all invalid items in your inventory which cause a game crash" << std::endl;
    std::cout << "Before continuing, make sure you have the game open and the character with the issues in question loaded\n" << std::endl;

    system("pause");

    std::cout << "\nLoading Dark Souls 2..." << std::endl;
    auto ds2 = dll_injector("DarkSoulsII.exe");

    std::cout << "Loading the discardItems dll..." << std::endl;

    std::string dllName = "discardItems.dll";
    std::ifstream file(dllName.c_str());

    if(file.good()){
        std::cout << "discardItems.dll found in program directory, running local copy" << std::endl;
        std::string filePath = ExePath();
        filePath = filePath + "\\" + dllName;
        ds2.inject_dll(filePath.c_str());
    } else {
        std::cout << "discardItems.dll not found, extracting a copy instead" << std::endl;
        std::filesystem::path dllPath = extractDll();
        ds2.inject_dll(WStringToString(dllPath).c_str());
    }


    std::cout << "Loading the dll thread...\n" << std::endl;
    std::cout << "Upon continuing, this window will close and a new window will open with more instructions. It may or may not appear behind your dark souls 2 window.\n" << std::endl;
    system("pause");
    ds2.execute_dll();


    return 0;
}


