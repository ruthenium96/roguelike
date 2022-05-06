#include "Artefact.h"

namespace world::state::object {
common::ObjectType Artefact::getObjectType() const {
    return common::ObjectType::ARTEFACT;
}

Artefact::Artefact(const Identity &identity) : AbstractObject(identity) {
    // TODO: can we have static container with this names?
    // set artefact "interactable"
    setProperty("interactable", std::make_any<bool>(true));
}
}  // namespace world::state::object