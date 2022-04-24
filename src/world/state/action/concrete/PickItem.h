#ifndef ARCH_ROGUELIKE_PICKITEM_H
#define ARCH_ROGUELIKE_PICKITEM_H

#include "../AbstractAction.h"

namespace world::state::action {
class PickItem : public AbstractAction {
  public:
    explicit PickItem(const std::optional<Identity>& selfIdentity);

    bool precondition(const object::Observer&, const action::Observer&) override;

    void changeTarget(object::Observer& observer, action::Observer& set) override;
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_PICKITEM_H
