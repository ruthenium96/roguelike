#ifndef ARCH_ROGUELIKE_STATE_H
#define ARCH_ROGUELIKE_STATE_H

#include "action/AbstractAction.h"
#include "object/Observer.h"
#include "object/concrete/Player.h"
#include <memory>
#include <set>

namespace world::state {

// State of World. Keeps Objects in object::Observer and Actions.
class State {
  public:
    State() = default;
    // Const and non-const getters of object::Observer
    const object::Observer& getObjectObserver() const;
    object::Observer& getObjectObserver();
    // Const and non-const getters of action::Observer
    const action::Observer& getActionObserver() const;
    action::Observer& getActionObserver();

    // Add action to array of Actions
    void addAction(const std::shared_ptr<action::AbstractAction>&);

    // Apply Action to array of Actions and object::Observer
    // Returns true if Action was applied
    bool applyAction(const std::shared_ptr<action::AbstractAction>&);

    void applyEveryTurnInternalActions();

    bool operator==(const State& rhs) const;

    bool operator!=(const State& rhs) const;

  private:
    object::Observer objectObserver_;
    action::Observer actionObserver_;
};

}  // namespace world::state

#endif  // ARCH_ROGUELIKE_STATE_H
