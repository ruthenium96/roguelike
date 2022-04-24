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

void State::applyAction(const std::shared_ptr<action::AbstractAction>& action) {
    if (action->precondition(objectObserver_, actionObserver_)) {
        action->changeTarget(objectObserver_, actionObserver_);
    }
}

}  // namespace world::state