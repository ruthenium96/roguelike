#ifndef ARCH_ROGUELIKE_OBJECTTYPE_H
#define ARCH_ROGUELIKE_OBJECTTYPE_H

namespace common {

enum class ObjectType {
    PLAYER,
    FLOOR,
    WALL,
    ARTEFACT,
    NPC,
    MOLD,
};

}  // namespace common

#endif  // ARCH_ROGUELIKE_OBJECTTYPE_H
