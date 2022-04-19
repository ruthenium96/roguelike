#include "PlayerInteract.h"

namespace world::state::action {
    bool PlayerInteract::precondition(const object::Observer &objectObserver,
                                      const std::set<std::shared_ptr<AbstractAction>> &set) {
        auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
        auto objects = objectObserver.getObjects(playerCoordinate);
        if (findInteractableObject(objects) != std::nullopt) {
            return true;
        } else {
            return false;
        }
    }

    void PlayerInteract::changeTarget(object::Observer &objectObserver, std::set<std::shared_ptr<AbstractAction>> &set) {
        auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
        auto objects = objectObserver.getObjects(playerCoordinate);
        auto interactableObject = findInteractableObject(objects).value();

    }

    std::optional<std::shared_ptr<object::AbstractObject>>
    PlayerInteract::findInteractableObject(const std::vector<std::shared_ptr<object::AbstractObject>> &objects) {
        for (const auto& object : objects) {
            if (object->getProperty("interactable").has_value()) {
                return object;
            }
        }
        return std::nullopt;
    }
}