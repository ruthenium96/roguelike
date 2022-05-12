#include "PickDropItem.h"
#include "../../object/concrete/Artefact.h"

#include <algorithm>

namespace world::state::action {
PickDropItem::PickDropItem(const std::optional<Identity>& selfIdentity) : AbstractAction(selfIdentity) {}

bool PickDropItem::precondition(const object::Observer& objectObbserver, const action::Observer& actionObserver) {
    // TODO: it is true only if it was called from PlayerInteract
    return true;
}

void PickDropItem::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {

    auto artefactIdentity = getCorrespondingObjectIdentity().value();
    auto maybeArtefact = objectObserver.getObject(artefactIdentity);
    if (maybeArtefact.has_value()) { // Pick branch:
        // first, move Item from Artefact to Player
        auto artefact = maybeArtefact.value();
        moveItem(artefact, objectObserver.getPlayer());
        // secondly, delete Artefact from ObjectObserver
        objectObserver.deleteObject(artefactIdentity);
    } else { // Drop branch:
        // first, create Artefact:
        auto artefact = std::make_shared<object::Artefact>(artefactIdentity);
        artefact->getCoordinate() = objectObserver.getPlayer()->getCoordinate();
        objectObserver.addObject(artefact);
        // second, move Item from Player to Artefact
        moveItem(objectObserver.getPlayer(), artefact);
    }
}

void PickDropItem::moveItem(std::shared_ptr<object::AbstractObject> from,
                            std::shared_ptr<object::AbstractObject> to) {
    for (size_t i = 0; i < from->getItems().size(); ++i) {
        if (from->getItems()[i]->getSelfIdentity() == getCorrespondingItemIdentity()) {
            auto item = std::move(from->getItems()[i]);
            from->getItems()[i] = std::move(from->getItems().back());
            from->getItems().pop_back();

            item->setNewHolderIdentity(to->getIdentity());
            to->getItems().emplace_back(std::move(item));
        }
    }

}
}  // namespace world::state::action
