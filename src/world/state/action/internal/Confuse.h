#ifndef ARCH_ROGUELIKE_CONFUSE_H
#define ARCH_ROGUELIKE_CONFUSE_H

#include "../AbstractAction.h"
#include "../npc/AbstractNPC.h"


namespace world::state::action {

// corresponding object is confused object
class Confuse : public AbstractNPC {
public:
    Confuse(const std::optional<Identity> &selfIdentity, Identity confusedObjectIdentity, int32_t duration, object::Observer &objectObserver, Observer &actionObserver);

    bool precondition(const object::Observer &objectObserver, const Observer &actionObserver) override;

    void changeTarget(object::Observer &objectObserver, Observer &actionObserver) override;

};

}

#endif //ARCH_ROGUELIKE_CONFUSE_H
