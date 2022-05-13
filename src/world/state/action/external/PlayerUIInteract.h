#ifndef ARCH_ROGUELIKE_PLAYERUIINTERACT_H
#define ARCH_ROGUELIKE_PLAYERUIINTERACT_H

#include "../AbstractAction.h"
#include "../../../../common/PlayerEquipment.h"

namespace world::state::action {
// Action from Engine to UI interact with something the Inventory Item
class PlayerUIInteract : public AbstractAction {
  public:
    PlayerUIInteract(common::ItemType itemType, common::EquipmentPosition position);

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;
  private:
    void wear(object::Observer &objectObserver);
    void unwear (object::Observer &objectObserver);
};
}
#endif //ARCH_ROGUELIKE_PLAYERUIINTERACT_H
