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
        Identity objectIdentity);

  private:
    std::set<std::shared_ptr<AbstractAction>> actions_;
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_ACTION_OBSERVER_H
