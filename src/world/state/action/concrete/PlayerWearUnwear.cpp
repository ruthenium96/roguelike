#include <cassert>
#include "PlayerWearUnwear.h"

namespace world::state::action {

PlayerWearUnwear::PlayerWearUnwear(common::ItemType itemType, common::EquipmentPosition position) : AbstractAction(std::nullopt) {
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

bool PlayerWearUnwear::precondition(const object::Observer &objectObserver, const Observer &actionObserver) {

    auto player = objectObserver.getPlayer();
    auto str_position = std::any_cast<std::string>(getProperty("position").value());
    auto itemType = std::any_cast<common::ItemType>(getProperty("itemToWear").value());

    if (player->getProperty(str_position).has_value()) { // unwear case
        // Unwear, if existed type equals wanted type
        auto existedItemType = std::any_cast<common::ItemType>(player->getProperty(str_position).value());
        return existedItemType == itemType;
    } else { // wear case
        return objectObserver.countHowManyTimesItemIsWearedByPlayer(itemType) < objectObserver.howManyItemsOfThisTypeHoldsPlayer(itemType);
    }
}

void PlayerWearUnwear::changeTarget(object::Observer &objectObserver, Observer &actionObserver) {
    auto player = objectObserver.getPlayer();
    auto itemType = std::any_cast<common::ItemType>(getProperty("itemToWear").value());
    auto str_position = std::any_cast<std::string>(getProperty("position").value());

    if (player->getProperty(str_position).has_value()) {  // unwear item
        player->deleteProperty(str_position);
    } else { // wear item
        player->setProperty(str_position, itemType);
    }
}
}