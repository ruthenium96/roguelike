#include "State.h"

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
    for (auto& internalAction : getActionObserver().getEveryTurnActions()) {
        applyAction(internalAction);
    }
}

}  // namespace world::state