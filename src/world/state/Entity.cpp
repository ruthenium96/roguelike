#include "Entity.h"
#include <cassert>

namespace world::state {

const std::map<std::string, std::any>& Entity::getAllProperties() const {
    return property_;
}

bool Entity::compareTwoAny(const std::any& lhs, const std::any& rhs) {
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
    if (lhs.type() == typeid(float)) {
        return std::any_cast<float>(lhs) == std::any_cast<float>(rhs);
    }
    assert(0);
}

void Entity::deleteProperty(const std::string& property_name) {
    property_.erase(property_name);
}

void Entity::setProperty(const std::string& property_name, std::any value) {
    // TODO: avoid changing of value type?
    property_[property_name] = std::move(value);
}

std::optional<std::any> Entity::getProperty(const std::string& property_name) const {
    if (property_.count(property_name) == 0) {
        return std::nullopt;
    } else {
        return property_.at(property_name);
    }
}

}  // namespace world::state