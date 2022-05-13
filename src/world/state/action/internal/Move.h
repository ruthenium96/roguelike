#ifndef ARCH_ROGUELIKE_MOVE_H
#define ARCH_ROGUELIKE_MOVE_H

#include "../AbstractAction.h"

namespace world::state::action {

// Action of movement and attack.
class Move : public AbstractAction {
  public:
    Move(Identity movingObject, int32_t delta_x, int32_t delta_y);

    bool precondition(const object::Observer& objectObserver, const action::Observer&) override;

    void changeTarget(object::Observer&, action::Observer&) override;

  private:
    void attack(std::shared_ptr<object::AbstractObject>& attacker, std::shared_ptr<object::AbstractObject>& defender);
};

}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_MOVE_H
