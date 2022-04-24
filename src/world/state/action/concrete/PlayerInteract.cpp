#include "PlayerInteract.h"
#include "PickItem.h"

namespace world::state::action
{
bool PlayerInteract::precondition(const object::Observer& objectObserver,
                                  const std::set<std::shared_ptr<AbstractAction>>& set)
{
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjects(playerCoordinate);
    if (findInteractableObject(objects) != std::nullopt)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PlayerInteract::changeTarget(object::Observer& objectObserver, std::set<std::shared_ptr<AbstractAction>>& set)
{
    auto playerCoordinate = objectObserver.getPlayer()->getCoordinate();
    auto objects = objectObserver.getObjects(playerCoordinate);
    auto interactableObject = findInteractableObject(objects).value();
    if (interactableObject->getObjectType() != common::ObjectType::ARTEFACT)
    {
        // do not support other ObjectTypes now
        return;
    }

    auto interactableObjectIdentity = interactableObject->getIdentity();

    auto maybe_action = findInteraction(interactableObjectIdentity, set);
    if (!maybe_action.has_value())
    {
        return;
    }
    auto action = maybe_action.value();
    action->changeTarget(objectObserver, set);
}

std::optional<std::shared_ptr<object::AbstractObject>> PlayerInteract::findInteractableObject(
    const std::vector<std::shared_ptr<object::AbstractObject>>& objects)
{
    for (const auto& object : objects)
    {
        if (object->getProperty("interactable").has_value())
        {
            return object;
        }
    }
    return std::nullopt;
}

std::optional<std::shared_ptr<action::AbstractAction>> PlayerInteract::findInteraction(
    Identity objectIdentity,
    const std::set<std::shared_ptr<AbstractAction>>& set)
{
    for (auto& action : set)
    {
        if (action->getCorrespondingObjectIdentity() == objectIdentity)
        {
            return action;
        }
    }
    return std::nullopt;
}
}  // namespace world::state::action