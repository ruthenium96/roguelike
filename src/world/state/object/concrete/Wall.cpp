#include "Wall.h"

namespace world::state::object {
common::ObjectType Wall::getObjectType() const {
    return common::WALL;
}
}