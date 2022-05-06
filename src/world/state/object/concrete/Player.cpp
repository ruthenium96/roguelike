#include "Player.h"
#include <any>

namespace world::state::object {
common::ObjectType Player::getObjectType() const {
    return common::ObjectType::PLAYER;
}

Player::Player(const Identity& identity) : AbstractObject(identity) {
    property_["hp"] = std::make_any<int32_t>(100);
    property_["lvl"] = std::make_any<int32_t>(1);
    property_["exp"] = std::make_any<int32_t>(0);
}

void Player::change_hp(int32_t value) {
    int32_t curr_hp = std::any_cast<int32_t>(property_["hp"]);
    int32_t updated_hp = curr_hp - value;

    property_["hp"] = std::make_any<int32_t>(updated_hp);
}

}  // namespace world::state::object