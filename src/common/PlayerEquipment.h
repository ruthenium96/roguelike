#ifndef ARCH_ROGUELIKE_PLAYEREQUIPMENT_H
#define ARCH_ROGUELIKE_PLAYEREQUIPMENT_H

#include "ItemType.h"
#include <optional>

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
}  // namespace common

#endif  // ARCH_ROGUELIKE_PLAYEREQUIPMENT_H
