#include "Move.h"
#include "Confuse.h"
#include <algorithm>

namespace world::state::action {

Move::Move(Identity movingObject, int32_t delta_x, int32_t delta_y) : AbstractAction(std::nullopt) {
    setCorrespondingObjectIdentity(movingObject);
    setProperty("dx", std::make_any<int32_t>(delta_x));
    setProperty("dy", std::make_any<int32_t>(delta_y));
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
                // MAYBE
                int32_t duration = 3;
                auto confuseAction = std::make_shared<Confuse>(state::IdentityGenerator::getNewIdentity(),
                                                               anotherObject->getIdentity(),
                                                               3,
                                                               objectObserver, actionObserver);
                actionObserver.addAction(confuseAction);
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

void Move::attack(std::shared_ptr<object::AbstractObject> &attacker,
                  std::shared_ptr<object::AbstractObject> &defender) {
    auto attacker_attack = std::any_cast<int32_t>(attacker->getProperty("attack").value());
    auto defender_defence = std::any_cast<int32_t>(defender->getProperty("defence").value());

    int32_t damage = std::max(attacker_attack - defender_defence, 0);

    int32_t old_hp = std::any_cast<int32_t>(defender->getProperty("hp").value());
    defender->setProperty("hp", old_hp - damage);
}

}  // namespace world::state::action