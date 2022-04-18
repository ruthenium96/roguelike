#ifndef ARCH_ROGUELIKE_PLAYERMOVE_H
#define ARCH_ROGUELIKE_PLAYERMOVE_H

#include "../AbstractAction.h"

namespace world::state::action
{

// Action of Player movement. Currently, can be applied only from external source.
class PlayerMove : public AbstractAction {
public:
    PlayerMove(int32_t delta_x, int32_t delta_y);

    bool precondition(const object::Observer& objectObserver,
                      const std::set<std::shared_ptr<AbstractAction>>&) override;

    void changeTarget(object::Observer&, std::set<std::shared_ptr<AbstractAction>>&) override;

private:
    int32_t delta_x_;
    int32_t delta_y_;
};

} // namespace world::state::action

#endif // ARCH_ROGUELIKE_PLAYERMOVE_H
