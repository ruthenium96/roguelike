#ifndef ARCH_ROGUELIKE_STATE_H
#define ARCH_ROGUELIKE_STATE_H

#include <memory>
#include <set>

#include "object/concrete/Player.h"
#include "object/Observer.h"
#include "action/AbstractAction.h"

namespace world::state {
class State {
public:
    State() = default;
    const object::Observer& getObjectObserver() const;
    object::Observer& getObjectObserver();
    void addAction(const std::shared_ptr<action::AbstractAction>&);
    void applyAction(const std::shared_ptr<action::AbstractAction>&);

private:
    object::Observer objectObserver_;
    std::set<std::shared_ptr<action::AbstractAction>> actions_;
};
}

#endif //ARCH_ROGUELIKE_STATE_H
