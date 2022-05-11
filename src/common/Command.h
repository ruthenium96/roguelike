#pragma once

#include <variant>
#include "ItemType.h"
#include "PlayerEquipment.h"

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
struct World_ApplyItem {
    ItemType type;
    EquipmentPosition equipmentPosition;
};

struct World_DropItem {
    ItemType type;
};

struct Controller_Unknown {
  private:
    bool dummyField_ = false;
};

struct Ignore {
private:
    bool dummyField_ = false;
};

struct World_Interact {
private:
    bool dummyField_ = false;
};

struct Controller_ChangeRegime {
private:
    bool dummyField_ = false;
};

struct UI_ApplyItem {
private:
    bool dummyField_ = false;
};

struct UI_DropItem {
private:
    bool dummyField_ = false;
};

struct Controller_Exit {
private:
    bool dummyField_ = false;
};

using ControllerCommand = std::variant<
        // Internal Controller Commands:
        Controller_Unknown,
        Controller_ChangeRegime,
        Controller_Exit,
        // UI and World Commands:
        Ignore,
        Move,
        // UI Commands:
        UI_ApplyItem,
        UI_DropItem,
        // World Commands:
        World_ApplyItem,
        World_DropItem,
        World_Interact
        >;

}  // namespace common
