
#ifndef ARCH_ROGUELIKE_ACTIONTYPE_H
#define ARCH_ROGUELIKE_ACTIONTYPE_H

namespace world::state::action {
enum class ActionType {
    INSTANT_ACTION,
    PICK_ITEM,
    POISON,
    AGRESSIVE_NPC,
    COWARD_NPC,
    INACTIVE_NPC,
    CONFUSE,
};
}

#endif //ARCH_ROGUELIKE_ACTIONTYPE_H
