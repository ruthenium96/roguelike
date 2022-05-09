#include "PlayerInteract.h"

namespace world::state::action {
bool PlayerInteract::precondition(const object::Observer& objectObserver, const action::Observer& actionObserver) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjectsAtCoordinate(playerCoordinate);
    return findInteractableObject(objects) != std::nullopt;
}

void PlayerInteract::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjectsAtCoordinate(playerCoordinate);
    auto interactableObject = findInteractableObject(objects).value();
    if (interactableObject->getObjectType() != common::ObjectType::ARTEFACT) {
        // do not support other ObjectTypes now
        return;
    }

    auto interactableObjectIdentity = interactableObject->getIdentity();

    // We know Artefact Identity, but do not know Identity
    // thus we have to find item through Artefact
    auto maybe_action = actionObserver.getActionByCorrespondingObjectIdentity(interactableObjectIdentity);
    if (!maybe_action.has_value()) {
        return;
    }
    auto action = maybe_action.value();
    action->changeTarget(objectObserver, actionObserver);
}

std::optional<std::shared_ptr<object::AbstractObject>> PlayerInteract::findInteractableObject(
    const std::vector<std::shared_ptr<object::AbstractObject>>& objects) {
    for (const auto& object : objects) {
        if (object->getProperty("interactable").has_value()) {
            return object;
        }
    }
    return std::nullopt;
}
}  // namespace world::state::action
