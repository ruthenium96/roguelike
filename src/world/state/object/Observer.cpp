#include "Observer.h"
namespace world::state::object {

std::shared_ptr<object::Player> world::state::object::Observer::getPlayer() {
    for (const auto& [_, object] : identityObjectMap_) {
        if (object->getObjectType() == common::ObjectType::PLAYER) {
            auto ptrToPlayer = std::dynamic_pointer_cast<Player>(object);
            return ptrToPlayer;
        }
    }
    return nullptr;
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

    std::vector<std::shared_ptr<AbstractObject>> Observer::getObjects(common::Coordinate coordinate) const {
        std::vector<std::shared_ptr<AbstractObject>> answer;
        for (const auto& [_, object] : identityObjectMap_) {
            if (object->getCoordinate() == coordinate) {
                answer.push_back(object);
            }
        }
        return answer;
    }

    std::shared_ptr<const object::Player> Observer::getPlayer() const {
        for (const auto& [_, object] : identityObjectMap_) {
            if (object->getObjectType() == common::ObjectType::PLAYER) {
                auto ptrToPlayer = std::dynamic_pointer_cast<Player>(object);
                return ptrToPlayer;
            }
        }
        return nullptr;
    }
}