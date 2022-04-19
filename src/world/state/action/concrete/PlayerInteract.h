#ifndef ARCH_ROGUELIKE_PLAYERINTERACT_H
#define ARCH_ROGUELIKE_PLAYERINTERACT_H

#include "../AbstractAction.h"

namespace world::state::action {
class PlayerInteract : public AbstractAction{
public:

    PlayerInteract() : AbstractAction(std::nullopt) {};

    bool precondition(const object::Observer &observer, const std::set<std::shared_ptr<AbstractAction>> &set) override;

    void changeTarget(object::Observer &observer, std::set<std::shared_ptr<AbstractAction>> &set) override;
private:
    std::optional<std::shared_ptr<object::AbstractObject>> findInteractableObject(const std::vector<std::shared_ptr<object::AbstractObject>>& objects);
    std::optional<std::shared_ptr<action::AbstractAction>> findInteraction(Identity objectIdentity, const std::set<std::shared_ptr<AbstractAction>> &set);
};
}

#endif //ARCH_ROGUELIKE_PLAYERINTERACT_H
