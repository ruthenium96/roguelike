#include "PlayerMove.h"
#include <algorithm>

namespace world::state::action {

PlayerMove::PlayerMove(int32_t delta_x, int32_t delta_y) : AbstractAction(std::nullopt) {
    setProperty("dx", std::make_any<int32_t>(delta_x));
    setProperty("dy", std::make_any<int32_t>(delta_y));
}

bool PlayerMove::precondition(const object::Observer& objectObserver, const action::Observer&) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto dx = std::any_cast<int32_t>(getProperty("dx").value());
    auto dy = std::any_cast<int32_t>(getProperty("dy").value());
    common::Coordinate wantedCoordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
    auto objects = objectObserver.getObjectsAtCoordinate(wantedCoordinate);
    for (const auto& object : objects) {
        if (object->getProperty("blocking") != std::nullopt) {
            return false;
        }
    }
    return true;
}

void PlayerMove::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto player = objectObserver.getPlayer();
    auto dx = std::any_cast<int32_t>(getProperty("dx").value());
    auto dy = std::any_cast<int32_t>(getProperty("dy").value());
    player->getCoordinate().x += dx;
    player->getCoordinate().y += dy;
}

}  // namespace world::state::action