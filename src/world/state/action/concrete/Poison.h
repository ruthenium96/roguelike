#ifndef ARCH_ROGUELIKE_POISON_H
#define ARCH_ROGUELIKE_POISON_H

#include "../AbstractAction.h"

namespace world::state::action {
class Poison : public AbstractAction {
public:
    Poison(Identity selfIdentity, int32_t hp_decrease, int32_t duration);

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;

private:
    int32_t hp_decrease_;
    int32_t duration_;
};
}

#endif //ARCH_ROGUELIKE_POISON_H
