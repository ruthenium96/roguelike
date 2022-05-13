#ifndef ARCH_ROGUELIKE_AGGRESSIVENPC_H
#define ARCH_ROGUELIKE_AGGRESSIVENPC_H

#include "../AbstractAction.h"
namespace world::state::action {

class AggressiveNPC : public AbstractAction {
public:
    AggressiveNPC(const std::optional<Identity> &selfIdentity);

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;

private:
    std::optional<std::shared_ptr<AbstractAction>> findDirection(const object::Observer &objectObserver, const action::Observer &actionObserver, int32_t dx_with_player, int32_t dy_with_player);
    std::optional<std::shared_ptr<AbstractAction>> contructAndTryMove(const object::Observer &objectObserver, const action::Observer &actionObserver, int32_t dx_try_step, int32_t dy_try_step);
    void death(object::Observer &objectObserver, action::Observer &actionObserver);
};
}

#endif //ARCH_ROGUELIKE_AGGRESSIVENPC_H
