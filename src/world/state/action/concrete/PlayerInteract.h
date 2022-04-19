#ifndef ARCH_ROGUELIKE_PLAYERINTERACT_H
#define ARCH_ROGUELIKE_PLAYERINTERACT_H

#include "../AbstractAction.h"

namespace world::state::action {
class PlayerInteract : public AbstractAction{
public:
    bool precondition(const object::Observer &observer, const std::set<std::shared_ptr<AbstractAction>> &set) override;

    void changeTarget(object::Observer &observer, std::set<std::shared_ptr<AbstractAction>> &set) override;
private:
    std::optional<std::shared_ptr<object::AbstractObject>> findInteractableObject(const std::vector<std::shared_ptr<object::AbstractObject>>& objects);
};
}

#endif //ARCH_ROGUELIKE_PLAYERINTERACT_H
