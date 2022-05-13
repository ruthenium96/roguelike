#ifndef ARCH_ROGUELIKE_ACTION_OBSERVER_H
#define ARCH_ROGUELIKE_ACTION_OBSERVER_H

#include "AbstractAction.h"
#include <set>

namespace world::state::action {
class AbstractAction;

class Observer {
  public:
    void addAction(const std::shared_ptr<action::AbstractAction>& action);
    void deleteAction(Identity actionIdentity);
    std::optional<std::shared_ptr<action::AbstractAction>> getActionByCorrespondingObjectIdentity(
        Identity objectIdentity) const;
    std::optional<std::shared_ptr<action::AbstractAction>> getActionByCorrespondingItemIdentity(
            Identity objectIdentity) const;
    const std::vector<std::shared_ptr<AbstractAction>>& getEveryTurnActions() const;
    const std::set<std::shared_ptr<AbstractAction>>& getAllActions() const;

    bool operator==(const Observer &rhs) const;
    bool operator!=(const Observer &rhs) const;

private:
    std::set<std::shared_ptr<AbstractAction>> allActions_;
    mutable std::vector<std::shared_ptr<AbstractAction>> everyMoveActions_;
    void updateRepresentations() const;
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_ACTION_OBSERVER_H
