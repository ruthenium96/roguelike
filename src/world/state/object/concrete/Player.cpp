#include "Player.h"
#include <any>

namespace world::state::object {
common::ObjectType Player::getObjectType() const {
    return common::ObjectType::PLAYER;
}

Player::Player(const Identity& identity) : AbstractObject(identity) {
    setProperty("hp", std::make_any<int32_t>(100));
    setProperty("lvl", std::make_any<int32_t>(1));
    setProperty("exp", std::make_any<int32_t>(0));
}

}  // namespace world::state::object