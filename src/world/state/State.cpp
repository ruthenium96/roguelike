#include "State.h"

namespace world::state
{

const object::Observer& State::getObjectObserver() const
{
    return objectObserver_;
}

object::Observer& State::getObjectObserver()
{
    return objectObserver_;
}

void State::addAction(const std::shared_ptr<action::AbstractAction>& action)
{
    actions_.insert(action);
}

void State::applyAction(const std::shared_ptr<action::AbstractAction>& action)
{
    if (action->precondition(objectObserver_, actions_))
    {
        action->changeTarget(objectObserver_, actions_);
    }
}

}  // namespace world::state