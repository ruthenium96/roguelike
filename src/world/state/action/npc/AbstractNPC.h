#ifndef ARCH_ROGUELIKE_ABSTRACTNPC_H
#define ARCH_ROGUELIKE_ABSTRACTNPC_H

#include "../AbstractAction.h"
namespace world::state::action {
// An abstract NPC class. ALso is required for NPC's death.
class AbstractNPC : public AbstractAction {
  public:
    explicit AbstractNPC(const std::optional<Identity>& selfIdentity);

    bool precondition(const object::Observer& observer, const Observer& observer1) override;

  protected:
    void death(object::Observer& objectObserver, action::Observer& actionObserver);
    std::optional<std::shared_ptr<AbstractAction>> contructAndTryMove(const object::Observer& objectObserver,
                                                                      const action::Observer& actionObserver,
                                                                      int32_t dx_try_step,
                                                                      int32_t dy_try_step);
};

}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_ABSTRACTNPC_H
