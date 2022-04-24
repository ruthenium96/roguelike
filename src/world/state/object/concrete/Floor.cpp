#include "Floor.h"

namespace world::state::object
{
common::ObjectType Floor::getObjectType() const
{
    return common::ObjectType::FLOOR;
}
}  // namespace world::state::object