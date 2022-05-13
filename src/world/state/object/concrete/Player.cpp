#include "Player.h"
#include <any>

namespace world::state::object {
common::ObjectType Player::getObjectType() const {
    return common::ObjectType::PLAYER;
}

Player::Player(const Identity& identity) : AbstractObject(identity) {
    setProperty("hp", std::make_any<int32_t>(100));
    setProperty("lvl", std::make_any<int32_t>(1));
    setProperty("xp", std::make_any<int32_t>(0));
    setProperty("attack", std::make_any<int32_t>(10));
    setProperty("defence", std::make_any<int32_t>(0));
    setProperty("vision", std::make_any<int32_t>(10));
    setProperty("blocking", std::make_any<bool>(true));
}

}  // namespace world::state::object