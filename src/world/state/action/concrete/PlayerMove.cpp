#include "PlayerMove.h"
#include <algorithm>

namespace world::state::action {
    PlayerMove::PlayerMove(int32_t delta_x, int32_t delta_y) {
        delta_x_ = delta_x;
        delta_y_ = delta_y;
    }

    bool PlayerMove::precondition(const object::Observer &objectObserver,
                                  const std::set<std::shared_ptr<AbstractAction>>&) {
        auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
        common::Coordinate wantedCoordinate = {playerCoordinate.x + delta_x_,
                                               playerCoordinate.y + delta_y_};
        auto objectTypes = objectObserver.getObjectsTypes(wantedCoordinate);
        return std::find(objectTypes.begin(), objectTypes.end(), common::WALL) == objectTypes.end();
    }

    void PlayerMove::changeTarget(object::Observer &objectObserver, std::set<std::shared_ptr<AbstractAction>>&) {
        auto player = objectObserver.getPlayer();
        player->getCoordinate().x += delta_x_;
        player->getCoordinate().y += delta_y_;
    }

}