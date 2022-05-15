#ifndef ARCH_ROGUELIKE_RING_H
#define ARCH_ROGUELIKE_RING_H

#include "../AbstractItem.h"

namespace world::state::item {
class Ring : public AbstractItem {
  public:
    Ring(const Identity& itemIdentity, const Identity& objectHolderIdentity);
    ;

    common::ItemType getItemType() const override { return common::ItemType::RING; };
};
}  // namespace world::state::item

#endif  // ARCH_ROGUELIKE_RING_H
