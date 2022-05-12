#include "AbstractObject.h"

#include <stdexcept>

namespace world::state::object {

bool AbstractObject::operator==(const AbstractObject &rhs) const {
    if (std::tie(selfIdentity_, coordinate_) !=
    std::tie(rhs.selfIdentity_, rhs.coordinate_)) {
        return false;
    }

    if (items_.size() != rhs.items_.size()) {
        return false;
    }
    for (size_t i = 0; i < items_.size(); ++i) {
        if (*items_[i] != *rhs.items_[i]) {
            return false;
        }
    }

    if (getAllProperties().size() != rhs.getAllProperties().size()) {
        return false;
    }
    auto liter = getAllProperties().begin();
    auto riter = rhs.getAllProperties().begin();
    while (liter != getAllProperties().end()) {
        if (liter->first != riter->first) {
            return false;
        }
        if (!compareTwoAny(liter->second, riter->second)) {
            return false;
        }
        ++liter;
        ++riter;
    }

    return true;
}

bool AbstractObject::operator!=(const AbstractObject &rhs) const {
    return !(rhs == *this);
}
}  // namespace world::state::object