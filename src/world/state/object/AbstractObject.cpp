#include "AbstractObject.h"

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
}  // namespace world::state::object