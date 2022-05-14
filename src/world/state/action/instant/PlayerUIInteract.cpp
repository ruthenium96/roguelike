#include <cassert>
#include "PlayerUIInteract.h"

namespace world::state::action {

PlayerUIInteract::PlayerUIInteract(common::ItemType itemType, common::EquipmentPosition position) : AbstractAction(std::nullopt) {
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

bool PlayerUIInteract::precondition(const object::Observer &objectObserver, const Observer &actionObserver) {

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

void PlayerUIInteract::changeTarget(object::Observer &objectObserver, Observer &actionObserver) {
    auto player = objectObserver.getPlayer();
    auto str_position = std::any_cast<std::string>(getProperty("position").value());

    if (player->getProperty(str_position).has_value()) {  // unwear item
        unwear(objectObserver);
    } else { // wear item
        wear(objectObserver);
    }
}

void PlayerUIInteract::wear(object::Observer &objectObserver) {
    auto player = objectObserver.getPlayer();
    auto itemType = std::any_cast<common::ItemType>(getProperty("itemToWear").value());
    auto str_position = std::any_cast<std::string>(getProperty("position").value());

    player->setProperty(str_position, itemType);

    // TODO: reimplement using constant from item.property_
    if (itemType == common::ItemType::STICK) {
        auto old_attack = std::any_cast<int32_t>(player->getProperty("attack").value());
        int32_t dattack = 1;
        player->setProperty("attack", old_attack + dattack);
    } else if (itemType == common::ItemType::RING) {
        auto old_defence = std::any_cast<int32_t>(player->getProperty("defence").value());
        int32_t ddefence = 1;
        player->setProperty("defence", old_defence + ddefence);
    }
}

void PlayerUIInteract::unwear(object::Observer &objectObserver) {
    auto player = objectObserver.getPlayer();
    auto itemType = std::any_cast<common::ItemType>(getProperty("itemToWear").value());
    auto str_position = std::any_cast<std::string>(getProperty("position").value());

    player->deleteProperty(str_position);

    // TODO: reimplement using constant from item.property_
    if (itemType == common::ItemType::STICK) {
        auto old_attack = std::any_cast<int32_t>(player->getProperty("attack").value());
        int32_t dattack = 1;
        player->setProperty("attack", old_attack - dattack);
    } else if (itemType == common::ItemType::RING) {
        auto old_defence = std::any_cast<int32_t>(player->getProperty("defence").value());
        int32_t ddefence = 1;
        player->setProperty("defence", old_defence - ddefence);
    }
}

ActionType PlayerUIInteract::getActionType() const {
    return ActionType::INSTANT_ACTION;
}

}