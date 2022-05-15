#include "Wall.h"

namespace world::state::object {
common::ObjectType Wall::getObjectType() const {
    return common::ObjectType::WALL;
}

Wall::Wall(const Identity& identity) : AbstractObject(identity) {
    setProperty("blocking", std::make_any<bool>(true));
}
}  // namespace world::state::object