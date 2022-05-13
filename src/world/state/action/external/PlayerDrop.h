#ifndef ARCH_ROGUELIKE_PLAYERDROP_H
#define ARCH_ROGUELIKE_PLAYERDROP_H

#include "../AbstractAction.h"
#include "../../../../common/ItemType.h"

namespace world::state::action {
// Action from Engine to drop the Item
class PlayerDrop : public AbstractAction {
  public:
    explicit PlayerDrop(common::ItemType itemType);

    bool precondition(const object::Observer &objectObserver, const action::Observer &actionObserver) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;

  private:
    // TODO: DRY, the same function exists in PlayerInteract
    std::optional<std::shared_ptr<object::AbstractObject>> findInteractableObject(
            const std::vector<std::shared_ptr<object::AbstractObject>>& objects);

};
}

#endif //ARCH_ROGUELIKE_PLAYERDROP_H
