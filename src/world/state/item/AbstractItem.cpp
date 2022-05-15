#include "AbstractItem.h"
#include <tuple>

namespace world::state::item {
const Identity& AbstractItem::getSelfIdentity() const {
    return selfIdentity_;
}

void AbstractItem::setNewHolderIdentity(const Identity& newHolderIdentity) {
    objectHolderIdentity_ = newHolderIdentity;
}

const Identity& AbstractItem::getObjectHolderIdentity() const {
    return objectHolderIdentity_;
}

bool AbstractItem::operator==(const AbstractItem& rhs) const {
    // TODO: also compare the types
    return std::tie(selfIdentity_, objectHolderIdentity_) == std::tie(rhs.selfIdentity_, rhs.objectHolderIdentity_);
}

bool AbstractItem::operator!=(const AbstractItem& rhs) const {
    return !(rhs == *this);
}
}  // namespace world::state::item
