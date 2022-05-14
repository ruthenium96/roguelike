#include <cassert>
#include "PlayerWorldInteract.h"

namespace world::state::action {
bool PlayerWorldInteract::precondition(const object::Observer& objectObserver, const action::Observer& actionObserver) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjectsAtCoordinate(playerCoordinate);
    return findInteractableObject(objects) != std::nullopt;
}

void PlayerWorldInteract::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjectsAtCoordinate(playerCoordinate);
    auto interactableObject = findInteractableObject(objects).value();

    auto interactableObjectIdentity = interactableObject->getIdentity();

    // We know Artefact Identity, but do not know Item Identity
    // thus we have to find item through Artefact
    auto allObjectActions = actionObserver.getActionsByCorrespondingObjectIdentity(interactableObjectIdentity);
    assert(!allObjectActions.empty());
    for (auto& action : allObjectActions) {
        if (action->getProperty("interaction").has_value() && std::any_cast<bool>(action->getProperty("interaction").value())) {
            action->changeTarget(objectObserver, actionObserver);
            return;
        }
    }
    assert(0);
}

std::optional<std::shared_ptr<object::AbstractObject>> PlayerWorldInteract::findInteractableObject(
    const std::vector<std::shared_ptr<object::AbstractObject>>& objects) {
    for (const auto& object : objects) {
        if (object->getProperty("interactable").has_value()) {
            return object;
        }
    }
    return std::nullopt;
}

ActionType PlayerWorldInteract::getActionType() const {
    return ActionType::INSTANT_ACTION;
}
}  // namespace world::state::action
