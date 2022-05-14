#include "Move.h"
#include "../internal/Confuse.h"
#include "../../../RandomNumberGenerator.h"
#include <algorithm>

namespace world::state::action {

Move::Move(Identity movingObject, int32_t delta_x, int32_t delta_y) : AbstractAction(std::nullopt) {
    setCorrespondingObjectIdentity(movingObject);
    setProperty("dx", std::make_any<int32_t>(delta_x));
    setProperty("dy", std::make_any<int32_t>(delta_y));
    // default value:
    setProperty("confuseThreshold", std::make_any<float>(0.7f));
}

bool Move::precondition(const object::Observer& objectObserver, const action::Observer&) {
    auto objectIdentity = getCorrespondingObjectIdentity().value();
    auto object = objectObserver.getObject(objectIdentity).value();
    auto objectCoordinate = object->getCoordinate();
    auto dx = std::any_cast<int32_t>(getProperty("dx").value());
    auto dy = std::any_cast<int32_t>(getProperty("dy").value());
    common::Coordinate wantedCoordinate = {objectCoordinate.x + dx, objectCoordinate.y + dy};
    auto objects = objectObserver.getObjectsAtCoordinate(wantedCoordinate);
    for (const auto& anotherObject : objects) {
        if (anotherObject->getProperty("blocking") != std::nullopt) {
            // if blocking, only can attack
            // but cannot attack object with the same objectType
            return (anotherObject->getProperty("hp").has_value() && anotherObject->getObjectType() != object->getObjectType());
        }
    }
    return true;
}

void Move::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto objectIdentity = getCorrespondingObjectIdentity().value();
    auto object = objectObserver.getObject(objectIdentity).value();

    auto player = objectObserver.getPlayer();
    auto dx = std::any_cast<int32_t>(getProperty("dx").value());
    auto dy = std::any_cast<int32_t>(getProperty("dy").value());

    common::Coordinate wantedCoordinate = {object->getCoordinate().x + dx, object->getCoordinate().y + dy};

    for (auto& anotherObject: objectObserver.getObjectsAtCoordinate(wantedCoordinate)) {
        if (anotherObject->getProperty("hp").has_value() && anotherObject->getObjectType() != object->getObjectType()) {
            attack(object, anotherObject);
            if (object == objectObserver.getPlayer()) {
                float probability = RandomNumberGenerator::generate();
                auto threshold = std::any_cast<float>(getProperty("confuseThreshold").value());
                if (probability > threshold) {
                    int32_t duration = 4;
                    auto confuseAction = std::make_shared<Confuse>(state::IdentityGenerator::getNewIdentity(),
                                                                   anotherObject->getIdentity(),
                                                                   duration,
                                                                   objectObserver, actionObserver);
                    actionObserver.addAction(confuseAction);
                }
            }
            return;
        }
    }

    for (auto& anotherObject: objectObserver.getObjectsAtCoordinate(wantedCoordinate)) {
        if (anotherObject->getProperty("blocking").has_value()) {
            return;
        }
    }

    object->getCoordinate().x += dx;
    object->getCoordinate().y += dy;
}

ActionType Move::getActionType() const {
    return ActionType::INSTANT_ACTION;
}

}  // namespace world::state::action