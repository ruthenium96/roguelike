#include "Floor.h"

namespace world::state::object {
common::ObjectType Floor::getObjectType() const {
    return common::FLOOR;
}
}