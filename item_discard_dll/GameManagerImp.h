//
// Created by false on 6/2/2024.
//

#ifndef DS2_INVENTORY_CLEANER_GAMEMANAGERIMP_H
#define DS2_INVENTORY_CLEANER_GAMEMANAGERIMP_H

#include "PointerChain.h"

using ItemInventory2BagListPtr = decltype(PointerChain::make<void*>(uintptr_t(), 0xA8, 0x10, 0xD0));

const int ITEM_STRUCT_SIZE = 0x28;
const int ITEM_UPGRADE_OFFSET = 0x11;
const int ITEM_ID_OFFSET = 0x14;

struct inventoryItem {
    uint8_t* prevPtr;
    uint8_t* nextPtr;
    char unk1[0x4];
    uint32_t itemID1;
    uint32_t itemID2;
    uint32_t index;
    float durability;
    uint8_t unk2;
    uint8_t upgrade;
    uint8_t infusion;
    uint8_t unk3;
};



class Address {
protected:
    void* address;
public:
    Address(void* address) :address(address) {};
    void* GetAddress() {
        return address;
    }
};

class GameManagerImp : public Address
{
private:
    ItemInventory2BagListPtr ItemInventory2BagList;
    uint8_t *InventoryPtr;
    GameManagerImp(void** address);


public:
    static GameManagerImp Make();
    bool isLoaded();
    void* getItemInventory2BagList();
    inventoryItem *readItem(int index);

};

#endif //DS2_INVENTORY_CLEANER_GAMEMANAGERIMP_H
