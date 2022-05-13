#include "Mold.h"

namespace world::state::object {
Mold::Mold(const Identity &identity) : AbstractObject(identity) {
    // the only way to kill the Mold -- interact with it
    setProperty("interactable", std::make_any<bool>(true));
}

common::ObjectType Mold::getObjectType() const {
    return common::ObjectType::MOLD;
}
}