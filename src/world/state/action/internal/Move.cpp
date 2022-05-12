#include "Move.h"
#include <algorithm>

namespace world::state::action {

Move::Move(int32_t delta_x, int32_t delta_y) : AbstractAction(std::nullopt) {
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
            return false;
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
    object->getCoordinate().x += dx;
    object->getCoordinate().y += dy;
}

}  // namespace world::state::action