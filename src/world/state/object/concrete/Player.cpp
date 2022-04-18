#include "Player.h"

namespace world::state::object {
common::ObjectType Player::getObjectType() const {
    return common::ObjectType::PLAYER;
}
}