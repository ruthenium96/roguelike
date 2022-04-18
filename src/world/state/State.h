#ifndef ARCH_ROGUELIKE_STATE_H
#define ARCH_ROGUELIKE_STATE_H

#include <memory>
#include <set>

#include "object/concrete/Player.h"
#include "object/Observer.h"
#include "action/AbstractAction.h"

namespace world::state
{

// State of World. Keeps Objects in object::Observer and Actions.
class State {
public:
    State() = default;
    // Const and non-const getters of object::Observer
    const object::Observer& getObjectObserver() const;
    object::Observer& getObjectObserver();
    
    // Add action to array of Actions
    void addAction(const std::shared_ptr<action::AbstractAction>&);
    
    // Apply Action to array of Actions and object::Observer
    void applyAction(const std::shared_ptr<action::AbstractAction>&);

private:
    object::Observer objectObserver_;
    std::set<std::shared_ptr<action::AbstractAction>> actions_;
};

} // namespace world::state

#endif // ARCH_ROGUELIKE_STATE_H
