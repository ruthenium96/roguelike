#include "Observer.h"

namespace world::state::action {
void Observer::addAction(const std::shared_ptr<action::AbstractAction>& action) {
    actions_.insert(action);
}

std::optional<std::shared_ptr<action::AbstractAction>> Observer::getActionByCorrespondingObjectIdentity(
    Identity objectIdentity) {
    for (auto& action : actions_) {
        if (action->getCorrespondingObjectIdentity() == objectIdentity) {
            return action;
        }
    }
    return std::nullopt;
}

void Observer::deleteAction(Identity actionIdentity) {
    for (const auto& action : actions_) {
        if (action->getSelfIdentity() == actionIdentity) {
            actions_.erase(action);
            break;
        }
    }
}
}  // namespace world::state::action