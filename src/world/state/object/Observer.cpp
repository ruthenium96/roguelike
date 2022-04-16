#include "Observer.h"
namespace world::state::object {

std::shared_ptr<object::AbstractObject> world::state::object::Observer::getPlayer() {
    // TODO: fix it
    return identityObjectMap_[Identity(0)];
}

std::optional<std::shared_ptr<object::AbstractObject>> Observer::getObject(Identity identity) {
    if (identityObjectMap_.count(identity) == 0) {
        return std::nullopt;
    } else {
        return identityObjectMap_[identity];
    }
}

    void Observer::addObject(const std::shared_ptr<object::AbstractObject>& object) {
    // TODO: check if identity is already exists
        identityObjectMap_[object->getIdentity()] = object;
    }

}