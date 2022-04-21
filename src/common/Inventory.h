#ifndef ARCH_ROGUELIKE_INVENTORY_H
#define ARCH_ROGUELIKE_INVENTORY_H

#include "ItemType.h"

namespace common {
struct ItemData {
    ItemType itemType;
    std::string description;
    // TODO: does the item get on Player?
};

using Inventory = std::vector<ItemData>;
}

#endif //ARCH_ROGUELIKE_INVENTORY_H
