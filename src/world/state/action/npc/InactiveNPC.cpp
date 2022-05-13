#include "InactiveNPC.h"

namespace world::state::action {
InactiveNPC::InactiveNPC(const std::optional<Identity> &selfIdentity) : AbstractNPC(selfIdentity) {}

void InactiveNPC::changeTarget(object::Observer &objectObserver, action::Observer &actionObserver) {
    auto NPCIdentity = getCorrespondingObjectIdentity().value();
    auto NPCObject = objectObserver.getObject(NPCIdentity).value();

    auto hp = std::any_cast<int32_t>(NPCObject->getProperty("hp").value());
    if (hp <= 0) {
        death(objectObserver, actionObserver);
        return;
    }
}
}