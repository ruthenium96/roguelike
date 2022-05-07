#include "AbstractObject.h"

#include <stdexcept>
#include <utility>

namespace world::state::object {
std::optional<std::any> AbstractObject::getProperty(const std::string& property_name) const {
    if (property_.count(property_name) == 0) {
        return std::nullopt;
    } else {
        return property_.at(property_name);
    }
}

void AbstractObject::setProperty(const std::string& property_name, std::any value) {
    // TODO: avoid changing of value type?
    property_[property_name] = std::move(value);
}

const std::map<std::string, std::any> &AbstractObject::getAllProperties() const {
    return property_;
}

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

    if (property_.size() != rhs.property_.size()) {
        return false;
    }
    auto liter = property_.begin();
    auto riter = rhs.property_.begin();
    while (liter != property_.end()) {
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

bool AbstractObject::compareTwoAny(const std::any &lhs, const std::any &rhs) {
    if (lhs.type() != rhs.type()) {
        return false;
    }
    if (lhs.type() == typeid(bool)) {
        return std::any_cast<bool>(lhs) == std::any_cast<bool>(rhs);
    }
    if (lhs.type() == typeid(uint64_t)) {
        return std::any_cast<uint64_t>(lhs) == std::any_cast<uint64_t>(rhs);
    }
    if (lhs.type() == typeid(int32_t)) {
        return std::any_cast<int32_t>(lhs) == std::any_cast<int32_t>(rhs);
    }
    throw std::invalid_argument("Unimplemented type for any comparison");
}
}  // namespace world::state::object