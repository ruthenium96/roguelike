#ifndef ARCH_ROGUELIKE_POISON_H
#define ARCH_ROGUELIKE_POISON_H

#include "../AbstractAction.h"

namespace world::state::action {
class Poison : public AbstractAction {
// Action for Poisoning of Object.
public:
    // default constructor
    explicit Poison(std::optional<Identity> selfIdentity);
    Poison(std::optional<Identity> selfIdentity, int32_t hp_decrease, int32_t duration);

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;

        ActionType getActionType() const override;
    };
}

#endif //ARCH_ROGUELIKE_POISON_H
