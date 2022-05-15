#include "MoldInteraction.h"

namespace world::state::action {

MoldInteraction::MoldInteraction(const std::optional<Identity>& selfIdentity) : AbstractAction(selfIdentity) {
    setProperty("interaction", true);
}

ActionType MoldInteraction::getActionType() const {
    return ActionType::MOLD_INTERACTION;
}

bool MoldInteraction::precondition(const object::Observer& objectObserver, const action::Observer& actionObserver) {
    // true, if it was called from WorldInteract
    return true;
}

void MoldInteraction::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto player = objectObserver.getPlayer();
    player->levelUp(5);

    auto moldObjectIdentity = getCorrespondingObjectIdentity().value();
    auto moldActions = actionObserver.getActionsByCorrespondingObjectIdentity(moldObjectIdentity);

    for (auto& moldAction : moldActions) {
        actionObserver.deleteAction(moldAction->getSelfIdentity().value());
    }
    objectObserver.deleteObject(moldObjectIdentity);
}

}  // namespace world::state::action