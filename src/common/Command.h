#pragma once

#include <variant>
#include "ItemType.h"

// This class helps modules communicate each other.
namespace common {

enum class Direction {
    TOP,
    LEFT,
    RIGHT,
    BOTTOM,
};

struct Move {
    Direction direction;
};

struct UiMoveInventory {
    Direction direction;
};

// TODO: rename this struct to something like "WearItem"
struct ApplyItem {
    ItemType type;
};

struct DropItem {
    ItemType type;
};

enum class NonparameterizedVariant {
    UNKNOWN,
    IGNORE,
    INTERACT,
    // can we use it as internal Controller State?
    UI_ACTIVATE_INVENTORY,
    UI_INVENTORY_APPLY,
    UI_INVENTORY_DROP,
    EXIT
};

using ControllerCommand = std::variant<
        NonparameterizedVariant,
        Move,
        UiMoveInventory,
        ApplyItem,
        DropItem
        >;

}  // namespace common
