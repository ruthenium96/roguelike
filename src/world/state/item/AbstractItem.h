#ifndef ARCH_ROGUELIKE_ABSTRACTITEM_H
#define ARCH_ROGUELIKE_ABSTRACTITEM_H

#include "../Identity.h"
#include <utility>

namespace world::state::item {

class AbstractItem {
public:
    AbstractItem(Identity&& itemIdentity, Identity&& objectHolderIdentity ) : itemIdentity_(itemIdentity), objectHolderIdentity_(objectHolderIdentity) {};
    AbstractItem(Identity&& itemIdentity, const Identity& objectHolderIdentity ) : itemIdentity_(itemIdentity), objectHolderIdentity_(objectHolderIdentity) {};
    AbstractItem(const Identity& itemIdentity, const Identity& objectHolderIdentity ) : itemIdentity_(itemIdentity), objectHolderIdentity_(objectHolderIdentity) {};

private:
    Identity itemIdentity_;
    Identity objectHolderIdentity_;
};

}

#endif //ARCH_ROGUELIKE_ABSTRACTITEM_H
