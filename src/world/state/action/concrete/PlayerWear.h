#ifndef ARCH_ROGUELIKE_PLAYERWEAR_H
#define ARCH_ROGUELIKE_PLAYERWEAR_H

#include "../AbstractAction.h"
#include "../../../../common/PlayerEquipment.h"

namespace world::state::action {
class PlayerWear : public AbstractAction {
  public:
    PlayerWear(common::ItemType itemType, common::EquipmentPosition position);

    bool precondition(const object::Observer &observer, const Observer &observer1) override;

    void changeTarget(object::Observer &observer, Observer &observer1) override;
};
}
#endif //ARCH_ROGUELIKE_PLAYERWEAR_H
