#include <valarray>
#include "AbstractNPC.h"
#include "../internal/Move.h"


namespace world::state::action {

AbstractNPC::AbstractNPC(const std::optional<Identity> &selfIdentity) : AbstractAction(selfIdentity) {
    setProperty("every_turn", std::make_any<bool>(true));
}

bool AbstractNPC::precondition(const object::Observer &objectObserver, const action::Observer &actionObserver) {
    // true if NPC can see Player
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto NPCIdentity = getCorrespondingObjectIdentity().value();
    auto NPCObject = objectObserver.getObject(NPCIdentity).value();
    auto NPCCoordinate = NPCObject->getCoordinate();
    auto vision = std::any_cast<int32_t>(NPCObject->getProperty("vision").value());
    int32_t dx = (playerCoordinate.x - NPCCoordinate.x);
    int32_t dy = (playerCoordinate.y - NPCCoordinate.y);
    return sqrt(dx * dx + dy * dy) < vision;
}

void AbstractNPC::death(object::Observer &objectObserver, Observer &actionObserver) {
    // TODO: move it from here
    auto player = objectObserver.getPlayer();
    auto old_xp = std::any_cast<int32_t>(player->getProperty("xp").value());
    auto new_xp = old_xp + 10;
    player->setProperty("xp", new_xp);

    int new_lvl = 0;
    uint32_t unew_xp = new_xp;
    while (unew_xp > 1) {
        unew_xp >>= 1;
        ++new_lvl;
    }
    player->setProperty("lvl", new_lvl);

    auto NPCIdentity = getCorrespondingObjectIdentity().value();
    objectObserver.deleteObject(NPCIdentity);

    deleteItselfFromActionObserver(actionObserver);

}

std::optional<std::shared_ptr<AbstractAction>>
AbstractNPC::contructAndTryMove(const object::Observer &objectObserver, const Observer &actionObserver,
                                int32_t dx_step_try, int32_t dy_step_try) {
    auto NPCIdentity = getCorrespondingObjectIdentity().value();

    auto tryMove = std::make_shared<Move>(dx_step_try, dy_step_try);
    tryMove->setCorrespondingObjectIdentity(NPCIdentity);
    if (tryMove->precondition(objectObserver, actionObserver)) {
        return tryMove;
    } else {
        return std::nullopt;
    }
}
}