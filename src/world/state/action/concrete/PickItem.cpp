#include "PickItem.h"

world::state::action::PickItem::PickItem(const std::optional<Identity>& selfIdentity) : AbstractAction(selfIdentity) {}

bool world::state::action::PickItem::precondition(const world::state::object::Observer& observer,
                                                  const std::set<std::shared_ptr<AbstractAction>>& set) {
    // TODO: it is true only if it was called from PlayerInteract
    return true;
}

void world::state::action::PickItem::changeTarget(world::state::object::Observer& observer,
                                                  std::set<std::shared_ptr<AbstractAction>>& set) {
    // first, move Item to player
    auto artefactIdentity = getCorrespondingObjectIdentity();
    auto artefact = observer.getObject(artefactIdentity.value()).value();
    auto item = std::move(artefact->getItems()[0]);
    observer.getPlayer()->getItems().push_back(std::move(item));
    // secondly, delete Artefact from ObjectObserver
    observer.deleteObject(artefactIdentity.value());
    // thirdly, delete PickItem itself
    deleteItselfFromSet(set);
}
