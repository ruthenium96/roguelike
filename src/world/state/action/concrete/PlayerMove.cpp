#include "PlayerMove.h"
#include <algorithm>

namespace world::state::action {

PlayerMove::PlayerMove(int32_t delta_x, int32_t delta_y) : AbstractAction(std::nullopt) {
    delta_x_ = delta_x;
    delta_y_ = delta_y;
}

bool PlayerMove::precondition(const object::Observer& objectObserver, const action::Observer&) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    common::Coordinate wantedCoordinate = {playerCoordinate.x + delta_x_, playerCoordinate.y + delta_y_};
    auto objects = objectObserver.getObjectsAtCoordinate(wantedCoordinate);
    for (const auto& object : objects) {
        if (object->getObjectType() == common::ObjectType::WALL) {
            return false;
        }
    }
    return true;
}

void PlayerMove::changeTarget(object::Observer& objectObserver, Observer&) {
    auto player = objectObserver.getPlayer();
    player->getCoordinate().x += delta_x_;
    player->getCoordinate().y += delta_y_;

    const int32_t hp_change_when_move{1};
    player->change_hp(hp_change_when_move);
}

}  // namespace world::state::action