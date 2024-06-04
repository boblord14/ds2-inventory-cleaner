//
// Created by false on 6/2/2024.
//

#ifndef DS2_INVENTORY_CLEANER_DISCARDFUNCTION_H
#define DS2_INVENTORY_CLEANER_DISCARDFUNCTION_H

#include "GameManagerImp.h"

using FnDiscardItem = void (*)(void* ItemInventory2BagList, uint32_t ItemIndex, uint32_t quantity);

class DiscardFunction{

private:
    void* ItemInventory2BagList;
    FnDiscardItem discardItemCall;

public:
    DiscardFunction(void* ItemInventory2BagList);
    void discardItem(uint32_t index);

};

#endif //DS2_INVENTORY_CLEANER_DISCARDFUNCTION_H
