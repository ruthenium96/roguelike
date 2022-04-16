#include "PlayerMove.h"

namespace world::state::action {
    PlayerMove::PlayerMove(int32_t delta_x, int32_t delta_y) {
        delta_x_ = delta_x;
        delta_y_ = delta_y;
    }

    bool PlayerMove::precondition(const object::Observer &objectObserver,
                                  const std::set<std::shared_ptr<AbstractAction>>&) {
        // TODO: check if move is possible
        return true;
    }

    void PlayerMove::changeTarget(object::Observer &objectObserver, std::set<std::shared_ptr<AbstractAction>>&) {
        auto player = objectObserver.getPlayer();
        player->getCoordinate().x += delta_x_;
        player->getCoordinate().y += delta_y_;
    }

}