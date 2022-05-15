#pragma once

#include "ItemType.h"
#include "PlayerEquipment.h"
#include "WorldUITransfer.h"
#include <variant>

// Trying to emulate healthy enums.
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

struct Interact {
  private:
    bool dummyField_ = false;
};

struct Controller_ChangeRegime {
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

struct Death {
  private:
    bool dummyField_ = false;
};

// This class helps modules communicate each other.
using Command = std::variant<
    // Controller => Controller:
    Controller_Unknown,
    Controller_ChangeRegime,
    Controller_Exit,
    // Controller => World/UI
    Move,
    Interact,
    // Controller => UI
    UI_DropItem,
    // UI => World
    Ignore,
    World_ApplyItem,
    World_DropItem,
    // World => Controller
    Death,
    // World => UI
    WorldUITransfer>;

}  // namespace common
