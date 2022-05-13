#ifndef ARCH_ROGUELIKE_PLAYEREQUIPMENT_H
#define ARCH_ROGUELIKE_PLAYEREQUIPMENT_H

#include <optional>
#include "ItemType.h"

namespace common {

enum EquipmentPosition {
    ARMOR,
    LEFTHAND,
    RIGHTHAND,
};

struct PlayerEquipment {
    std::optional<ItemType> armor;
    std::optional<ItemType> leftHand;
    std::optional<ItemType> rightHand;
};
}

#endif //ARCH_ROGUELIKE_PLAYEREQUIPMENT_H
