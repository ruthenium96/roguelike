#include "CowardNPC.h"

namespace world::state::action {

CowardNPC::CowardNPC(const std::optional<Identity> &selfIdentity) : AbstractNPC(selfIdentity) {}

void CowardNPC::changeTarget(object::Observer &objectObserver, action::Observer &actionObserver) {
    auto NPCIdentity = getCorrespondingObjectIdentity().value();
    auto NPCObject = objectObserver.getObject(NPCIdentity).value();

    auto hp = std::any_cast<int32_t>(NPCObject->getProperty("hp").value());
    if (hp <= 0) {
        death(objectObserver, actionObserver);
        return;
    }

    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto NPCCoordinate = NPCObject->getCoordinate();

    int32_t dx_with_player = (NPCCoordinate.x - playerCoordinate.x);
    int32_t dy_with_player = (NPCCoordinate.y - playerCoordinate.y);

    auto mbMoveAction = findDirection(objectObserver, actionObserver, dx_with_player, dy_with_player);
    if (mbMoveAction.has_value()) {
        mbMoveAction.value()->changeTarget(objectObserver, actionObserver);
    }
}

std::optional<std::shared_ptr<AbstractAction>>
CowardNPC::findDirection(const object::Observer &objectObserver, const Observer &actionObserver,
                         int32_t dx_with_player, int32_t dy_with_player) {
    {
        int32_t dx_step_try = (dx_with_player >= 0) ? 1 : -1;
        auto tryMove = contructAndTryMove(objectObserver, actionObserver, dx_step_try, 0);
        if (tryMove.has_value()) {
            return tryMove;
        }
    }
    {
        int32_t dy_step_try = (dy_with_player >= 0) ? 1 : -1;
        auto tryMove = contructAndTryMove(objectObserver, actionObserver, 0, dy_step_try);
        if (tryMove.has_value()) {
            return tryMove;
        }
    }
    return std::nullopt;
}

}