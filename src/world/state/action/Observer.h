#ifndef ARCH_ROGUELIKE_ACTION_OBSERVER_H
#define ARCH_ROGUELIKE_ACTION_OBSERVER_H

#include "AbstractAction.h"
#include <set>

namespace world::state::action {
class AbstractAction;
// Observer of Actions.
class Observer {
  public:
    // add new actiob
    void addAction(const std::shared_ptr<action::AbstractAction>& action);
    // delete new action
    void deleteAction(Identity actionIdentity);
    // Trying to get Actions by corresponding Identities
    std::optional<std::shared_ptr<action::AbstractAction>> getActionByCorrespondingObjectIdentity(
        Identity objectIdentity) const;
    std::optional<std::shared_ptr<action::AbstractAction>> getActionByCorrespondingItemIdentity(
            Identity objectIdentity) const;
    // gets all actions with property "every_turn"
    const std::vector<std::shared_ptr<AbstractAction>>& getEveryTurnActions() const;
    // gets all actions
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
