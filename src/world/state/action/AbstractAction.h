#ifndef ARCH_ROGUELIKE_ABSTRACTACTION_H
#define ARCH_ROGUELIKE_ABSTRACTACTION_H

#include "../object/Observer.h"
#include <set>

namespace world::state::action {
// Abstract class of Action -- something that changes Objects or other Actions.
class AbstractAction {
public:
    // It is precondition: should this Action be applied or not.
    virtual bool precondition(const object::Observer&, const std::set<std::shared_ptr<AbstractAction>>&) = 0;
    // Changes Object and Actions of interest.
    virtual void changeTarget(object::Observer&, std::set<std::shared_ptr<AbstractAction>>&) = 0;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTACTION_H
