#include "PickItem.h"
namespace world::state::action {
PickItem::PickItem(const std::optional<Identity> &selfIdentity)
        : AbstractAction(selfIdentity) {}

bool PickItem::precondition(const object::Observer &objectObbserver,
                                                  const action::Observer &actionObserver) {
    // TODO: it is true only if it was called from PlayerInteract
    return true;
}

void PickItem::changeTarget(object::Observer &objectObserver,
                            action::Observer &actionObserver) {
    // first, move Item to player
    auto artefactIdentity = getCorrespondingObjectIdentity();
    auto artefact = objectObserver.getObject(artefactIdentity.value()).value();
    auto item = std::move(artefact->getItems()[0]);
    objectObserver.getPlayer()->getItems().push_back(std::move(item));
    // secondly, delete Artefact from ObjectObserver
    objectObserver.deleteObject(artefactIdentity.value());
    // thirdly, delete PickItem itself
    deleteItselfFromActionObserver(actionObserver);
}
}

