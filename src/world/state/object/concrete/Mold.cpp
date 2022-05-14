#include "Mold.h"

namespace world::state::object {
Mold::Mold(const Identity &identity) : AbstractObject(identity) {
    // the only way to kill the Mold -- interact with it
    setProperty("interactable", std::make_any<bool>(true));
    setProperty("attack", std::make_any<int32_t>(2));
    setProperty("growingThreshold", std::make_any<float>(0.99f));
}

common::ObjectType Mold::getObjectType() const {
    return common::ObjectType::MOLD;
}
}