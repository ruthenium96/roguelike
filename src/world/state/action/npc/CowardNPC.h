#ifndef ARCH_ROGUELIKE_COWARDNPC_H
#define ARCH_ROGUELIKE_COWARDNPC_H

#include "AbstractNPC.h"
namespace world::state::action {
// Behaviour of Coward NPC.
class CowardNPC : public AbstractNPC {
public:
    explicit CowardNPC(const std::optional<Identity> &selfIdentity);

    void changeTarget(object::Observer &observer, Observer &observer1) override;
private:
    std::optional<std::shared_ptr<AbstractAction>> findDirection(const object::Observer &objectObserver, const action::Observer &actionObserver, int32_t dx_with_player, int32_t dy_with_player);

};
}

#endif //ARCH_ROGUELIKE_COWARDNPC_H
