#ifndef ARCH_ROGUELIKE_INACTIVENPC_H
#define ARCH_ROGUELIKE_INACTIVENPC_H

#include "AbstractNPC.h"
namespace world::state::action {
// Behaviour of Inactive NPC.
class InactiveNPC : public AbstractNPC {
  public:
    explicit InactiveNPC(const std::optional<Identity>& selfIdentity);

    void changeTarget(object::Observer& observer, Observer& observer1) override;

    ActionType getActionType() const override;
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_INACTIVENPC_H
