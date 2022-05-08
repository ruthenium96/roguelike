#include "PickDropItem.h"
namespace world::state::action {
PickDropItem::PickDropItem(const std::optional<Identity>& selfIdentity) : AbstractAction(selfIdentity) {}

bool PickDropItem::precondition(const object::Observer& objectObbserver, const action::Observer& actionObserver) {
    // TODO: it is true only if it was called from PlayerInteract
    return true;
}

void PickDropItem::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    // Pick branch:
    // first, move Item to player
    auto artefactIdentity = getCorrespondingObjectIdentity();
    auto artefact = objectObserver.getObject(artefactIdentity.value()).value();
    auto item = std::move(artefact->getItems()[0]);
    item->setNewHolderIdentity(objectObserver.getPlayer()->getIdentity());
    objectObserver.getPlayer()->getItems().push_back(std::move(item));
    // secondly, delete Artefact from ObjectObserver
    objectObserver.deleteObject(artefactIdentity.value());
    // thirdly, delete PickDropItem itself
    deleteItselfFromActionObserver(actionObserver);

    // TODO: drop branch
}
}  // namespace world::state::action
