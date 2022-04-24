#include "AbstractObject.h"

namespace world::state::object
{
std::optional<std::any> AbstractObject::getProperty(const std::string& property_name) const
{
    if (property_.count(property_name) == 0)
    {
        return std::nullopt;
    }
    else
    {
        return property_.at(property_name);
    }
}
}  // namespace world::state::object