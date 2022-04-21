#ifndef ARCH_ROGUELIKE_ABSTRACTITEM_H
#define ARCH_ROGUELIKE_ABSTRACTITEM_H

#include "../Identity.h"
#include <utility>
#include "../../../common/ItemType.h"

namespace world::state::item {

class AbstractItem {
public:
    AbstractItem(const Identity& itemIdentity, const Identity& objectHolderIdentity ) : selfIdentity_(itemIdentity), objectHolderIdentity_(objectHolderIdentity) {};

    void setNewHolderIdentity(const Identity& newHolderIdentity) {
        objectHolderIdentity_ = newHolderIdentity;
    }
    virtual common::ItemType getItemType() const = 0;
private:
    const Identity selfIdentity_;
    Identity objectHolderIdentity_;
};

}

#endif //ARCH_ROGUELIKE_ABSTRACTITEM_H
