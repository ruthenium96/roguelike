#ifndef ARCH_ROGUELIKE_ABSTRACTITEM_H
#define ARCH_ROGUELIKE_ABSTRACTITEM_H

#include "../../../common/ItemType.h"
#include "../Entity.h"
#include "../Identity.h"
#include <utility>

namespace world::state::item {
// Abstract class for Item.
class AbstractItem : public Entity {
  public:
    AbstractItem(const Identity& itemIdentity, const Identity& objectHolderIdentity)
        : selfIdentity_(itemIdentity), objectHolderIdentity_(objectHolderIdentity){};

    const Identity& getSelfIdentity() const;
    const Identity& getObjectHolderIdentity() const;

    void setNewHolderIdentity(const Identity& newHolderIdentity);
    virtual common::ItemType getItemType() const = 0;

    virtual ~AbstractItem() = default;

    bool operator==(const AbstractItem& rhs) const;

    bool operator!=(const AbstractItem& rhs) const;

  private:
    const Identity selfIdentity_;
    Identity objectHolderIdentity_;
};

}  // namespace world::state::item

#endif  // ARCH_ROGUELIKE_ABSTRACTITEM_H
