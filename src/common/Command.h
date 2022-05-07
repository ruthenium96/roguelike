#pragma once

// This class helps modules communicate each other.
namespace common {

enum class ControllerCommand {
    UNKNOWN,
    IGNORE,
    MOVE_TOP,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_BOTTOM,
    INTERACT,
    UI_ACTIVATE_INVENTORY,
    UI_INVENTORY_DOWN,
    UI_INVENTORY_UP,
    UI_INVENTORY_APPLY,
    UI_INVENTORY_DROP,
    APPLY_RING,
    APPLY_STICK,
    DROP_RING,
    DROP_STICK,
    EXIT
};

}  // namespace common
