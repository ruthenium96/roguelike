#include "PlayerDrop.h"

namespace world::state::action {

PlayerDrop::PlayerDrop(common::ItemType itemType) : AbstractAction(std::nullopt) {
    setProperty("itemToDrop", itemType);
}

bool PlayerDrop::precondition(const object::Observer &objectObserver, const action::Observer &actionObserver) {
    // TODO: also _assert_ that player have Item of ItemType
    // Cannot drop Item on the Coordinate with interactable object (for example, Artefact)
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjectsAtCoordinate(playerCoordinate);
    // NB: the opposite situation with PlayerInteract
    return findInteractableObject(objects) == std::nullopt;
}

void PlayerDrop::changeTarget(object::Observer &objectObserver, action::Observer &actionObserver) {
    auto player = objectObserver.getPlayer();
    auto requiredItemType = std::any_cast<common::ItemType>(getProperty("itemToDrop").value());
    for (const auto& item : player->getItems()) {
        // TODO: at first, try to drop unweared items?
        if (item->getItemType() == requiredItemType) {
            auto pickDropAction = actionObserver.getActionByCorrespondingItemIdentity(item->getSelfIdentity()).value();
            // NB: this function invalidates iterator
            pickDropAction->changeTarget(objectObserver, actionObserver);
            break;
        }
    }
}

std::optional<std::shared_ptr<object::AbstractObject>> PlayerDrop::findInteractableObject(
        const std::vector<std::shared_ptr<object::AbstractObject>> &objects) {
    for (const auto& object : objects) {
        if (object->getProperty("interactable").has_value()) {
            return object;
        }
    }
    return std::nullopt;
}
}