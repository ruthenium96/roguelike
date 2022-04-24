#include "Player.h"

namespace world::state::object {
common::ObjectType Player::getObjectType() const {
    return common::ObjectType::PLAYER;
}

Player::Player(Identity&& identity) : AbstractObject(std::move(identity)) {
    property_["hp"] = std::make_any<int32_t>(100);
    property_["lvl"] = std::make_any<int32_t>(1);
    property_["exp"] = std::make_any<int32_t>(0);
}
}  // namespace world::state::object