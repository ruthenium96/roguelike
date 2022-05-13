#include "Confuse.h"

namespace world::state::action {

Confuse::Confuse(const std::optional<Identity> &selfIdentity, Identity confusedObjectIdentity, int32_t duration,
                 object::Observer &objectObserver, Observer &actionObserver) : AbstractNPC(selfIdentity) {
    setProperty("every_turn", std::make_any<bool>(true));
    setProperty("duration", std::make_any<int32_t>(duration));
    setCorrespondingObjectIdentity(confusedObjectIdentity);
    // deactivate all actions of confused object
    for (auto& action : actionObserver.getAllActions()) {
        if (action->getCorrespondingObjectIdentity() == confusedObjectIdentity) {
            action->deleteProperty("every_turn");
        }
    }
}


bool Confuse::precondition(const object::Observer &objectObserver, const Observer &actionObserver) {
    return true;
}

void Confuse::changeTarget(object::Observer &objectObserver, Observer &actionObserver) {

    auto confusedObjectIdentity = getCorrespondingObjectIdentity().value();
    auto confusedObject = objectObserver.getObject(confusedObjectIdentity).value();
    auto hp = std::any_cast<int32_t>(confusedObject->getProperty("hp").value());
    if (hp <= 0) {
        death(objectObserver, actionObserver);
        return;
    }

    // TODO: CREATE MOVE

    auto duration = std::any_cast<int32_t>(getProperty("duration").value());
    --duration;
    setProperty("duration", std::make_any<int32_t>(duration));
    if (duration <= 0) {
        for (auto& action : actionObserver.getAllActions()) {
            // turn on previous actions...
            if (action->getCorrespondingObjectIdentity() == confusedObjectIdentity) {
                action->setProperty("every_turn", true);
            }
        }
        deleteItselfFromActionObserver(actionObserver);
    }
}

}