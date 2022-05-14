#ifndef ARCH_ROGUELIKE_MOLDEVERYTURN_H
#define ARCH_ROGUELIKE_MOLDEVERYTURN_H

#include "../AbstractAction.h"

namespace world::state::action {

class MoldEveryTurn : public AbstractAction {
public:
    explicit MoldEveryTurn(const std::optional<Identity> &selfIdentity);

    ActionType getActionType() const override;

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;

private:
    void grow(object::Observer &objectObserver, action::Observer &actionObserver, common::Coordinate wantedCoordinate);

};

}

#endif //ARCH_ROGUELIKE_MOLDEVERYTURN_H
