#include "AbstractItem.h"

namespace world::state::item {
const Identity &AbstractItem::getSelfIdentity() const {
    return selfIdentity_;
}

void AbstractItem::setNewHolderIdentity(const Identity &newHolderIdentity) {
    objectHolderIdentity_ = newHolderIdentity;
}

const Identity& AbstractItem::getObjectHolderIdentity() const {
    return objectHolderIdentity_;
}
}
