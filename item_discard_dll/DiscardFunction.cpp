//
// Created by false on 6/2/2024.
//

#include "Signature.h"
#include "DiscardFunction.h"

const uint32_t DISCARD_OFFSET = 0x1b3830;

DiscardFunction::DiscardFunction(void *ItemInventory2BagList) {
    this->ItemInventory2BagList = ItemInventory2BagList;

    ModuleData ds2Data("DarkSoulsII.exe");
    auto ds2Addr = reinterpret_cast<uint8_t*>(ds2Data.BaseAddress);

    void** discardCallIns = (void**)(ds2Addr + DISCARD_OFFSET);
    discardItemCall = reinterpret_cast<FnDiscardItem>(reinterpret_cast<uint8_t*>(discardCallIns));
}

void DiscardFunction::discardItem(uint32_t index) {
    discardItemCall(ItemInventory2BagList, index, 1);
}

