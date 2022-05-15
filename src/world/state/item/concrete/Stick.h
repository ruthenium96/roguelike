#ifndef ARCH_ROGUELIKE_STICK_H
#define ARCH_ROGUELIKE_STICK_H

#include "../AbstractItem.h"

namespace world::state::item {
class Stick : public AbstractItem {
  public:
    Stick(const Identity& itemIdentity, const Identity& objectHolderIdentity);
    ;

    common::ItemType getItemType() const override { return common::ItemType::STICK; };
};
}  // namespace world::state::item

#endif  // ARCH_ROGUELIKE_STICK_H
