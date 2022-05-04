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

namespace ui {

namespace {

// TODO: replace this crutchy function
size_t get_inventory_size(const common::Inventory& inventory) {
    std::unordered_map<common::ItemType, size_t> items;
    for (const auto& item : inventory) {
        items[item.itemType] += 1;
    }

    return items.size();
}

}  // namespace

UI::UI(const std::string& style) {
    if (style == "default") {
        style_ = std::make_unique<DefaultStyle>();
    } else {
        throw std::runtime_error("Style " + style + " is not implemented in UI.");
    }
}

void UI::apply_command(const common::ControllerCommand& command, const common::WorldUITransfer& world_state) {
    using common::ControllerCommand;

    switch (command) {
        case ControllerCommand::UI_ACTIVATE_INVENTORY:
            if (get_inventory_size(world_state.inventory)) {
                state_.inventory_active = true;
            }
            break;
        case ControllerCommand::UI_INVENTORY_DOWN:
            if (state_.inventory_active && get_inventory_size(world_state.inventory) &&
                (get_inventory_size(world_state.inventory) - 1 > state_.inventory_pos)) {
                ++state_.inventory_pos;
            }
            break;
        case ControllerCommand::UI_INVENTORY_UP:
            if (state_.inventory_active && state_.inventory_pos) {
                --state_.inventory_pos;
            }
            break;
        case ControllerCommand::UI_INVENTORY_APPLY:
            break;
        default:
            throw std::runtime_error("Unknown command sent to UI");
    }
}

void UI::deactivate_state() {
    state_ = {};
}

void UI::draw(const common::WorldUITransfer& world_state) {
    display_.fill_border();

    pushHelloOnDisplay();
    pushStatsOnDisplay(world_state.playerMetrics);
    pushMapOnDisplay(world_state.map);
    pushInventoryOnDisplay(world_state.inventory);

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
    const auto player_exp = std::to_string(player_stats.exp);

    size_t curr_display_height = 3;
    stats_display.put_string("Lvl  : " + player_lvl, curr_display_height++, 2U);
    stats_display.put_string("Exp  : " + player_exp, curr_display_height++, 2U);
    stats_display.put_string("HP   : " + player_hp, curr_display_height++, 2U);
    // stats_display.put_string("Mana : " + player_mana, curr_display_height++, 2U);

    const size_t game_board_stats_height_pos = 8U;
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

        if (state_.inventory_active && state_.inventory_pos == item_type_idx) {
            inventory_item_str += "<=";
        }

        inventory_display.put_string(inventory_item_str, inventory_line_idx, 2U);

        ++inventory_line_idx;
        ++item_type_idx;
    }

    const size_t game_board_inventory_height_pos = 17U;
    const size_t game_board_inventory_width_pos = 35U;
    display_.add_display_data(inventory_display, game_board_inventory_height_pos, game_board_inventory_width_pos);
}

}  // namespace ui