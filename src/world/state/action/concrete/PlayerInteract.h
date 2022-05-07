#ifndef ARCH_ROGUELIKE_PLAYERINTERACT_H
#define ARCH_ROGUELIKE_PLAYERINTERACT_H

#include "../AbstractAction.h"

namespace world::state::action {
class PlayerInteract : public AbstractAction {
  public:
    PlayerInteract() : AbstractAction(std::nullopt){};

    bool precondition(const object::Observer&, const action::Observer&) override;

    void changeTarget(object::Observer&, action::Observer&) override;

  private:
    std::optional<std::shared_ptr<object::AbstractObject>> findInteractableObject(
        const std::vector<std::shared_ptr<object::AbstractObject>>& objects);
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_PLAYERINTERACT_H
