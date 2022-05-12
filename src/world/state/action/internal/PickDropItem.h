#ifndef ARCH_ROGUELIKE_PICKDROPITEM_H
#define ARCH_ROGUELIKE_PICKDROPITEM_H

#include "../AbstractAction.h"

namespace world::state::action {
class PickDropItem : public AbstractAction {
  public:
    explicit PickDropItem(const std::optional<Identity>& selfIdentity);

    bool precondition(const object::Observer&, const action::Observer&) override;

    void changeTarget(object::Observer& observer, action::Observer& set) override;
    // always: correspondingObjectIdentity_ = artefactIdentity, even if Artefact does not exist
    // correspondingItemIdentity_ always is the same
  private:
    void moveItem(std::shared_ptr<object::AbstractObject> from, std::shared_ptr<object::AbstractObject> to);
};
}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_PICKDROPITEM_H
