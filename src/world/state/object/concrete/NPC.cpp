#include "NPC.h"

namespace world::state::object {
NPC::NPC(const Identity &identity) : AbstractObject(identity) {
    setProperty("hp", std::make_any<int32_t>(20));
    setProperty("attack", std::make_any<int32_t>(5));
    setProperty("defence", std::make_any<int32_t>(2));
    setProperty("vision", std::make_any<int32_t>(5));
}

common::ObjectType NPC::getObjectType() const {
    return common::ObjectType::NPC;
}
}