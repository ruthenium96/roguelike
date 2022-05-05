#include "Observer.h"

namespace world::state::action {
void Observer::addAction(const std::shared_ptr<action::AbstractAction>& action) {
    allActions_.insert(action);
    updateRepresentations();
}

std::optional<std::shared_ptr<action::AbstractAction>> Observer::getActionByCorrespondingObjectIdentity(
    Identity objectIdentity) const {
    for (auto& action : allActions_) {
        if (action->getCorrespondingObjectIdentity() == objectIdentity) {
            return action;
        }
    }
    return std::nullopt;
}

void Observer::deleteAction(Identity actionIdentity) {
    for (const auto& action : allActions_) {
        if (action->getSelfIdentity() == actionIdentity) {
            allActions_.erase(action);
            break;
        }
    }
    updateRepresentations();
}

const std::vector<std::shared_ptr<AbstractAction>>& Observer::getEveryTurnActions() const {
    return everyMoveActions_;
}

void Observer::updateRepresentations() {
    // update EveryMove Representation:
    everyMoveActions_.clear();
    for (const auto& action : allActions_) {
        if (action->isEveryTurn()) {
            everyMoveActions_.push_back(action);
        }
    }
}
}  // namespace world::state::action