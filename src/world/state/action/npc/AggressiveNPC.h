#ifndef ARCH_ROGUELIKE_AGGRESSIVENPC_H
#define ARCH_ROGUELIKE_AGGRESSIVENPC_H

#include "AbstractNPC.h"
namespace world::state::action {
// Behaviour of Aggressive NPC.
class AggressiveNPC : public AbstractNPC {
  public:
    explicit AggressiveNPC(const std::optional<Identity>& selfIdentity);

    void changeTarget(object::Observer& observer, Observer& observer1) override;

    ActionType getActionType() const override;

  private:
    std::optional<std::shared_ptr<AbstractAction>> findDirection(const object::Observer& objectObserver,
                                                                 const action::Observer& actionObserver,
                                                                 int32_t dx_with_player,
                                                                 int32_t dy_with_player);
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_AGGRESSIVENPC_H
