#ifndef ARCH_ROGUELIKE_MOLDINTERACTION_H
#define ARCH_ROGUELIKE_MOLDINTERACTION_H

#include "../AbstractAction.h"

namespace world::state::action {
class MoldInteraction : public AbstractAction{
public:
    explicit MoldInteraction(const std::optional<Identity> &selfIdentity);

    ActionType getActionType() const override;

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;
};
}

#endif //ARCH_ROGUELIKE_MOLDINTERACTION_H
