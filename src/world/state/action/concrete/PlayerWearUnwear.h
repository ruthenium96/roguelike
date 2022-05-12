#ifndef ARCH_ROGUELIKE_PLAYERWEARUNWEAR_H
#define ARCH_ROGUELIKE_PLAYERWEARUNWEAR_H

#include "../AbstractAction.h"
#include "../../../../common/PlayerEquipment.h"

namespace world::state::action {
class PlayerWearUnwear : public AbstractAction {
  public:
    PlayerWearUnwear(common::ItemType itemType, common::EquipmentPosition position);

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;
  private:
    void wear(object::Observer &objectObserver);
    void unwear (object::Observer &objectObserver);
};
}
#endif //ARCH_ROGUELIKE_PLAYERWEARUNWEAR_H
