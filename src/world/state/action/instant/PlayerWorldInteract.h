#ifndef ARCH_ROGUELIKE_PLAYERWORLDINTERACT_H
#define ARCH_ROGUELIKE_PLAYERWORLDINTERACT_H

#include "../AbstractAction.h"

namespace world::state::action {
// Action from Engine to World interact with other Object (namely, Artefact)
class PlayerWorldInteract : public AbstractAction {
  public:
    PlayerWorldInteract() : AbstractAction(std::nullopt){};

    bool precondition(const object::Observer&, const action::Observer&) override;

    void changeTarget(object::Observer&, action::Observer&) override;

    ActionType getActionType() const override;

private:
    std::optional<std::shared_ptr<object::AbstractObject>> findInteractableObject(
        const std::vector<std::shared_ptr<object::AbstractObject>>& objects);
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_PLAYERWORLDINTERACT_H
