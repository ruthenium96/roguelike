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

bool Observer::operator==(const Observer &rhs) const {
    if (allActions_.size() != rhs.allActions_.size()) {
        return false;
    }
    auto liter = allActions_.begin();
    auto riter = rhs.allActions_.begin();
    while (liter != allActions_.end()) {
        if (**(liter) != **(riter)) {
            return false;
        }
        ++liter;
        ++riter;
    }
    return true;
}

bool Observer::operator!=(const Observer &rhs) const {
    return !(rhs == *this);
}

const std::set<std::shared_ptr<AbstractAction>> &Observer::getAllActions() const {
    return allActions_;
}

std::optional<std::shared_ptr<action::AbstractAction>>
Observer::getActionByCorrespondingItemIdentity(Identity objectIdentity) const {
    for (auto& action : getAllActions()) {
        if (action->getCorrespondingItemIdentity() == objectIdentity) {
            return action;
        }
    }
    return std::nullopt;
}
}  // namespace world::state::action