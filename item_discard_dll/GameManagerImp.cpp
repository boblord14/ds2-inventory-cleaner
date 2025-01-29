//
// Created by false on 6/2/2024.
//

#include "GameManagerImp.h"
#include "Signature.h"

static void** GameManagerImpIns;

void** InitHelper() {
    ModuleData ds2Data("DarkSoulsII.exe");
    Signature gameManagerImpSig = Signature("48 8B 05 ?? ?? ?? ?? 48 8B 58 38 48 85 DB  74  ?? F6");
    GameManagerImpIns = (void**)gameManagerImpSig.Scan(&ds2Data, 0x3, 0x7);

    while((void*)*(uintptr_t*)GameManagerImpIns == nullptr){}

    return GameManagerImpIns;
}

GameManagerImp::GameManagerImp(void** add) : Address((void*)*(uintptr_t*)add),
                                             ItemInventory2BagList(*(uintptr_t*)add, 0xA8, 0x10, 0xD0){
    this->InventoryPtr = reinterpret_cast<uint8_t*>(*ItemInventory2BagList)+0x28;
}

bool GameManagerImp::isLoaded() {
    if (address) {
        return true;
    }
    else {
        return false;
    }
}

GameManagerImp GameManagerImp::Make() {
    GameManagerImpIns = InitHelper();
    if(*GameManagerImpIns != nullptr)
        return GameManagerImp(GameManagerImpIns);
    else return nullptr;
}

void *GameManagerImp::getItemInventory2BagList() {
    return *ItemInventory2BagList;
}

inventoryItem *GameManagerImp::readItem(int index) {
    auto item = reinterpret_cast<inventoryItem*>(InventoryPtr + (index*ITEM_STRUCT_SIZE));
    return item;
}
