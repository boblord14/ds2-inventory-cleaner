//
// Created by false on 6/2/2024.
//
#include <windows.h>
#include <iostream>
#include "Signature.h"
#include "GameManagerImp.h"
#include "DiscardFunction.h"

const int ITEMPARAM_FIRST_EQUIPMENT = 1000000;
const int ITEMPARAM_LAST_EQUIPMENT = 11840000;
const int INVENTORY_ITEM_CAP = 3839;
const int MAX_VALID = 10;
const int GESTURE_TYPE = 1;

DWORD WINAPI MainThread(LPVOID lpParam)
{

    AllocConsole();
    SetConsoleTitleA("DS2 Inventory Cleaner");

    FILE * pNewStdout = nullptr;
    ::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
    std::cout.clear();
    std::wcout.clear();

    std::cout << "Boblord's Dark Souls 2 Inventory Cleaner- Ingame DLL\n" << std::endl;
    std::cout << "Once more, make sure the character with the invalid items is loaded in before continuing\n" << std::endl;
    system("pause");

    GameManagerImp mainBase = GameManagerImp::Make();
    std::cout << "\nDependencies loaded" << std::endl;

    auto discard = DiscardFunction(mainBase.getItemInventory2BagList());

    std::cout << "\nReady to start discarding items\n" << std::endl;
    system("pause");

    int removedInvalidItems = 0;
    int removedGestureItems = 0;
    inventoryItem* itemStruct;

    for(int i=0; i<=INVENTORY_ITEM_CAP; i++){
        itemStruct = mainBase.readItem(i);
        if(itemStruct->itemID1 >= ITEMPARAM_FIRST_EQUIPMENT && itemStruct->itemID1 <= ITEMPARAM_LAST_EQUIPMENT){
            if(itemStruct->upgrade > MAX_VALID){
                discard.discardItem(itemStruct->index);
                removedInvalidItems++;
            }
        }else if(itemStruct->equipAdditionalType == GESTURE_TYPE){
            discard.discardItem(itemStruct->index);
            removedGestureItems++;
        }
    }

    std::cout << "\n" << removedInvalidItems << " items with invalid upgrade levels and "<< removedGestureItems
    << " items tagged as gestures removed from inventory. You should be able to open your inventory now." << std::endl;
    std::cout << "If further errors persist, try again or contact boblord for troubleshooting. \n" << std::endl;
    std::cout << "Press a key one more time to clean up and exit the program \n" << std::endl;
    system("pause");

    FreeConsole();
    ShowWindow(FindWindowA(nullptr, "DS2 Inventory Cleaner"), 0);
    HMODULE currentDll = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,(LPCSTR) &MainThread, &currentDll);
    FreeLibraryAndExitThread(currentDll, 0);
}


BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module);
        CreateThread(0, 0, &MainThread, nullptr, 0, nullptr);
    }
    return 1;
}