#ifndef ARCH_ROGUELIKE_ABSTRACTACTION_H
#define ARCH_ROGUELIKE_ABSTRACTACTION_H

#include "../object/Observer.h"
#include <set>

namespace world::state::action {
class AbstractAction {
public:
    virtual bool precondition(const object::Observer&, const std::set<std::shared_ptr<AbstractAction>>&) = 0;
    virtual void changeTarget(object::Observer&, std::set<std::shared_ptr<AbstractAction>>&) = 0;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTACTION_H
