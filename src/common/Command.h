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

struct Unknown {
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

struct ChangeRegime {
private:
    bool dummyField_ = false;
};

struct UIInventoryApply {
private:
    bool dummyField_ = false;
};

struct UIInventoryDrop {
private:
    bool dummyField_ = false;
};

struct Exit {
private:
    bool dummyField_ = false;
};

using ControllerCommand = std::variant<
        // Internal Controller Commands:
        Unknown,
        ChangeRegime,
        Exit,
        Ignore,
        Move,
        Interact,
        UiMoveInventory,
        UIInventoryApply,
        UIInventoryDrop,
        ApplyItem,
        DropItem
        >;

}  // namespace common
