#include "State.h"
#include <cassert>

namespace world::state {

const object::Observer& State::getObjectObserver() const {
    return objectObserver_;
}

object::Observer& State::getObjectObserver() {
    return objectObserver_;
}

void State::addAction(const std::shared_ptr<action::AbstractAction>& action) {
    actionObserver_.addAction(action);
}

bool State::applyAction(const std::shared_ptr<action::AbstractAction>& action) {
    if (action->precondition(objectObserver_, actionObserver_)) {
        action->changeTarget(objectObserver_, actionObserver_);
        return true;
    }
    return false;
}

const action::Observer& State::getActionObserver() const {
    return actionObserver_;
}

action::Observer& State::getActionObserver() {
    return actionObserver_;
}

void State::applyEveryTurnInternalActions() {
    auto currentEveryTurnActions = getActionObserver().getEveryTurnActions();
    for (auto& internalAction : currentEveryTurnActions) {
        assert(internalAction->getProperty("every_turn").has_value());
        applyAction(internalAction);
    }
}

bool State::operator==(const State& rhs) const {
    return std::tie(objectObserver_, actionObserver_) == std::tie(rhs.objectObserver_, rhs.actionObserver_);
}

bool State::operator!=(const State& rhs) const {
    return !(rhs == *this);
}

}  // namespace world::state