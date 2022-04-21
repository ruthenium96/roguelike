#include "Artefact.h"

namespace world::state::object {
    common::ObjectType Artefact::getObjectType() const {
        return common::ObjectType::ARTEFACT;
    }
}