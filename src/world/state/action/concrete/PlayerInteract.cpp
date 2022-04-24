#include "PlayerInteract.h"
#include "PickItem.h"

namespace world::state::action {
bool PlayerInteract::precondition(const object::Observer& objectObserver, const action::Observer& actionObserver) {
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjectsAtCoordinate(playerCoordinate);
    if (findInteractableObject(objects) != std::nullopt) {
        return true;
    } else {
        return false;
    }
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
}
}  // namespace world::state::action
