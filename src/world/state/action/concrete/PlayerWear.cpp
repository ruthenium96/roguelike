#include <cassert>
#include "PlayerWear.h"

namespace world::state::action {

PlayerWear::PlayerWear(common::ItemType itemType, common::EquipmentPosition position) : AbstractAction(std::nullopt) {
    setProperty("itemToWear", itemType);
    std::string str_position;
    if (position == common::ARMOR) {
        str_position = "armor";
    } else if (position == common::LEFTHAND) {
        str_position = "leftHand";
    } else if (position == common::RIGHTHAND) {
        str_position = "rightHand";
    } else {
        assert(0);
    }

    setProperty("position", str_position);
}

bool PlayerWear::precondition(const object::Observer &objectObserver, const Observer &actionObserver) {
    auto player = objectObserver.getPlayer();
    auto str_position = std::any_cast<std::string>(getProperty("position").value());
    if (player->getProperty("armor").has_value() && str_position == "armor") {
        return false;
    }
    if (player->getProperty("leftHand").has_value() && str_position == "leftHand") {
        return false;
    }
    if (player->getProperty("rightHand").has_value() && str_position == "rightHand") {
        return false;
    }
    return true;
}

void PlayerWear::changeTarget(object::Observer &objectObserver, Observer &actionObserver) {
    auto player = objectObserver.getPlayer();
    auto itemType = std::any_cast<common::ItemType>(getProperty("itemToWear").value());
    auto str_position = std::any_cast<std::string>(getProperty("position").value());

    player->setProperty(str_position, itemType);
}
}