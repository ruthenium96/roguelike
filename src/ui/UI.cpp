#include "UI.h"
#include "char_display.h"
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <optional>

namespace ui {

namespace {

// TODO: replace this crutchy functions
size_t get_inventory_size(const common::Inventory& inventory) {
    std::unordered_map<common::ItemType, size_t> items;
    for (const auto& item : inventory) {
        items[item.itemType] += 1;
    }

    return items.size();
}

std::optional<common::ItemType> get_inventory_item_type_by_index(const common::Inventory& inventory, size_t index) {
    std::unordered_map<common::ItemType, size_t> items;
    for (const auto& item : inventory) {
        items[item.itemType] += 1;
    }

    auto it = items.begin();
    std::advance(it, index);
    if (it != items.end()) {
        return it->first;
    } else {
        return std::nullopt;
    }
}

}  // namespace

UI::UI(const std::string& style) {
    if (style == "default") {
        style_ = std::make_unique<DefaultStyle>();
    } else {
        throw std::runtime_error("Style " + style + " is not implemented in UI.");
    }
}

common::ControllerCommand UI::apply_command(const common::ControllerCommand& command,
                                            const common::WorldUITransfer& world_state) {
    using common::ControllerCommand;

    if (std::holds_alternative<common::Interact>(command)) {
        auto item_type = get_inventory_item_type_by_index(world_state.inventory, state_.inventory_pos);
        if (item_type.has_value()) {
            // TODO: fix static_cast
            common::World_ApplyItem applyItem = {item_type.value(),
                                                 static_cast<common::EquipmentPosition>(state_.equipment_pos)};
            return applyItem;
        } else {
            // TODO: print something?
            return common::Ignore();
        }
    } else if (std::holds_alternative<common::UI_DropItem>(command)) {
        auto item_type = get_inventory_item_type_by_index(world_state.inventory, state_.inventory_pos);
        if (item_type.has_value()) {
            common::World_DropItem dropItem = {item_type.value()};
            return dropItem;
        } else {
            // TODO: print something? pushMessageOnDisplay?
            return common::Ignore();
        }

    } else if (std::holds_alternative<common::Ignore>(command)) {

    } else if (std::holds_alternative<common::Move>(command)) {
        auto variant = std::get<common::Move>(command);
        switch (variant.direction) {
            case common::Direction::TOP: {
                if (state_.active && state_.inventory_pos) {
                    --state_.inventory_pos;
                }
                break;
            }
            case common::Direction::BOTTOM: {
                if (state_.active && get_inventory_size(world_state.inventory) &&
                    (get_inventory_size(world_state.inventory) - 1 > state_.inventory_pos)) {
                    ++state_.inventory_pos;
                }
                break;
            }
            case common::Direction::LEFT: {
                if (state_.active && state_.equipment_pos != 0U) {
                    --state_.equipment_pos;
                }
                break;
            }
            case common::Direction::RIGHT: {
                if (state_.active && state_.equipment_pos != 2U) {
                    ++state_.equipment_pos;
                }
                break;
            }
        }
    } else {
        // Unknown, ChangeRegime, Exit, Move, Interact, ApplyItem, DropItem
        assert(0);
    }

    return common::Ignore();
}

void UI::deactivate_state(const common::WorldUITransfer& world_state) {
    state_ = {};
}

bool UI::activate_state(const common::WorldUITransfer& world_state) {
    if (get_inventory_size(world_state.inventory)) {
        state_.active = true;
        return true;
    }
    return false;
}


void UI::draw(const common::WorldUITransfer& world_state) {
    display_.fill_border();

    pushHelloOnDisplay();
    pushStatsOnDisplay(world_state.playerMetrics);
    pushMapOnDisplay(world_state.map);
    pushInventoryOnDisplay(world_state.inventory);
    pushEquipmentOnDisplay(world_state.playerEquipment);
    pushMessageOnDisplay(world_state.message);

    display_.draw();
}

void UI::pushHelloOnDisplay() {
    const size_t hello_display_height = 3U;
    const size_t hello_display_width = 46;
    CharDisplay hello_display(hello_display_height, hello_display_width);
    hello_display.fill_border();

    hello_display.put_string("Hello in Arch Roguelike 3000!", 1U, 9U);

    const size_t game_board_hello_height_pos = 0U;
    const size_t game_board_hello_width_pos = 5U;
    display_.add_display_data(hello_display, game_board_hello_height_pos, game_board_hello_width_pos);
}

void UI::pushStatsOnDisplay(const common::PlayerMetrics& player_stats) {
    const size_t stats_display_height = 8U;
    const size_t stats_display_width = 14U;
    CharDisplay stats_display(stats_display_height, stats_display_width);
    stats_display.fill_border();
    stats_display.put_string("Stats", 1U, 4U);
    stats_display.put_line_hor(2U, 0U, stats_display.width());

    const auto player_lvl = std::to_string(player_stats.lvl);
    const auto player_hp = std::to_string(player_stats.hp);
    const auto player_exp = std::to_string(player_stats.xp);

    size_t curr_display_height = 3;
    stats_display.put_string("Lvl  : " + player_lvl, curr_display_height++, 2U);
    stats_display.put_string("Exp  : " + player_exp, curr_display_height++, 2U);
    stats_display.put_string("HP   : " + player_hp, curr_display_height++, 2U);
    // stats_display.put_string("Mana : " + player_mana, curr_display_height++, 2U);

    const size_t game_board_stats_height_pos = 4U;
    const size_t game_board_stats_width_pos = 35U;
    display_.add_display_data(stats_display, game_board_stats_height_pos, game_board_stats_width_pos);
}

void UI::pushMapOnDisplay(const common::Map& map) {
    const size_t map_display_height = 23U;
    const size_t map_display_width = 23U;
    CharDisplay map_display(map_display_height, map_display_width);
    map_display.fill_border();

    auto initial_coordinate = map.begin()->first;
    auto width_i = 1U;
    auto height_i = 1U;

    for (const auto& [coordinate, objects] : map) {
        // currently only the last object is painted
        map_display.at(height_i, width_i) = style_->getGameObjectsRepr(objects);

        if (coordinate.y != initial_coordinate.y) {
            width_i = 1U;
            ++height_i;
            initial_coordinate = coordinate;
        } else {
            width_i++;
        }
    }

    const size_t game_board_map_height_pos = 4U;
    const size_t game_board_map_width_pos = 7U;
    display_.add_display_data(map_display, game_board_map_height_pos, game_board_map_width_pos);
}

namespace {
template <typename T>
std::string tostr_fixed_width(const T& value, size_t width = 3) {
    std::ostringstream os;
    os << std::setw(width) << value;
    return os.str();
}
}  // namespace

// pushes player inventory on a display
void UI::pushInventoryOnDisplay(const common::Inventory& inventory) {
    const size_t inventory_display_height = 7U;
    const size_t inventory_display_width = 14U;
    CharDisplay inventory_display(inventory_display_height, inventory_display_width);
    inventory_display.fill_border();
    inventory_display.put_string("Inventory", 1U, 2U);
    inventory_display.put_line_hor(2U, 0U, inventory_display.width());

    // TODO: move counting to Engine, change Inventory struct.
    std::unordered_map<common::ItemType, size_t> items;
    for (const auto& item : inventory) {
        items[item.itemType] += 1;
    }

    // size_t inventory_line_idx = 3;
    // for (const auto& [item_type, num_items] : items) {
    //     const auto item_type_str = std::string{style_->getGameItemRepr(item_type)};
    //     std::string inventory_item_str = std::to_string(num_items) + " " + item_type_str;

    //     inventory_display.put_string(inventory_item_str, inventory_line_idx, 4U);
    //     ++inventory_line_idx;
    // }

    size_t item_type_idx = 0;
    size_t inventory_line_idx = 3;
    // const size_t inventory_size = inventory_display_height - 4;

    for (const auto& [item_type, num_items] : items) {
        const auto item_type_str = std::string{style_->getGameItemRepr(item_type)};

        std::string inventory_item_str = tostr_fixed_width(num_items) + " " + item_type_str;

        if (state_.active && state_.inventory_pos == item_type_idx) {
            inventory_item_str += "<=";
        }

        inventory_display.put_string(inventory_item_str, inventory_line_idx, 2U);

        ++inventory_line_idx;
        ++item_type_idx;
    }

    const size_t game_board_inventory_height_pos = 12U;
    const size_t game_board_inventory_width_pos = 35U;
    display_.add_display_data(inventory_display, game_board_inventory_height_pos, game_board_inventory_width_pos);
}

void UI::pushMessageOnDisplay(const std::optional<std::string>& mbMessage) {
    std::string content;
    content.reserve(23U);
    if (mbMessage.has_value()) {
        content = mbMessage.value();
    }
    assert(content.size() <= 23);

    const size_t message_display_height = 1U;
    const size_t message_display_width = 23U;
    CharDisplay message_display(message_display_height, message_display_width);

    message_display.put_string(content, 0U, 0U);

    const size_t game_board_hello_height_pos = 27U;
    const size_t game_board_hello_width_pos = 7U;
    display_.add_display_data(message_display, game_board_hello_height_pos, game_board_hello_width_pos);
}

void UI::pushEquipmentOnDisplay(const common::PlayerEquipment &equipment) {
    const size_t equipment_display_height = 7U;
    const size_t equipment_display_width = 14U;
    CharDisplay equipment_display(equipment_display_height, equipment_display_width);
    equipment_display.fill_border();
    equipment_display.put_string("Equipment", 1U, 2U);
    equipment_display.put_line_hor(2U, 0U, equipment_display.width());

    size_t inventory_line_idx = 3;

    equipment_display.put_string("Ar LH RH", inventory_line_idx, 2U);
    ++inventory_line_idx;

    std::string wearedItems;

    // armor
    if (equipment.armor.has_value()) {
        auto item_type = equipment.armor.value();
        wearedItems += std::string{style_->getGameItemRepr(item_type)};
    } else {
        wearedItems += " ";
    }
    wearedItems += "  ";

    // left hand
    if (equipment.leftHand.has_value()) {
        auto item_type = equipment.leftHand.value();
        wearedItems += std::string{style_->getGameItemRepr(item_type)};
    } else {
        wearedItems += " ";
    }
    wearedItems += "  ";
    // right hand
    if (equipment.rightHand.has_value()) {
        auto item_type = equipment.rightHand.value();
        wearedItems += std::string{style_->getGameItemRepr(item_type)};
    } else {
        wearedItems += " ";
    }
    wearedItems += "  ";

    equipment_display.put_string(wearedItems, inventory_line_idx, 2U);
    ++inventory_line_idx;

    std::string choseString;
    if (state_.active) {
        if (state_.equipment_pos == 0) {
            choseString = "^        ";
        }
        if (state_.equipment_pos == 1) {
            choseString = "   ^     ";
        }
        if (state_.equipment_pos == 2) {
            choseString = "      ^  ";
        }
    }
    equipment_display.put_string(choseString, inventory_line_idx, 2U);

    const size_t game_board_equipment_height_pos = 19U;
    const size_t game_board_equipment_width_pos = 35U;
    display_.add_display_data(equipment_display, game_board_equipment_height_pos, game_board_equipment_width_pos);

}

}  // namespace ui