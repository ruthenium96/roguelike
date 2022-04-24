#ifndef ARCH_ROGUELIKE_ABSTRACTITEM_H
#define ARCH_ROGUELIKE_ABSTRACTITEM_H

#include "../../../common/ItemType.h"
#include "../Identity.h"
#include <utility>

namespace world::state::item {

class AbstractItem {
  public:
    AbstractItem(const Identity& itemIdentity, const Identity& objectHolderIdentity)
        : selfIdentity_(itemIdentity), objectHolderIdentity_(objectHolderIdentity){};

    void setNewHolderIdentity(const Identity& newHolderIdentity) { objectHolderIdentity_ = newHolderIdentity; }
    virtual common::ItemType getItemType() const = 0;

  private:
    const Identity selfIdentity_;
    Identity objectHolderIdentity_;
};

}  // namespace world::state::item

#endif  // ARCH_ROGUELIKE_ABSTRACTITEM_H
