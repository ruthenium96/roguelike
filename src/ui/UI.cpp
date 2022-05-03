#include "UI.h"
#include "char_display.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace ui {

UI::UI(const std::string& style) {
    if (style == "default") {
        style_ = std::make_unique<DefaultStyle>();
    } else {
        throw std::runtime_error("Style " + style + " is not implemented in UI.");
    }
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
    const size_t stats_display_height = 3U;
    const size_t stats_display_width = 46;
    CharDisplay stats_display(stats_display_height, stats_display_width);
    stats_display.fill_border();

    stats_display.put_string("Hello in Arch Roguelike 3000!", 1U, 9U);

    const size_t game_board_stats_height_pos = 0U;
    const size_t game_board_stats_width_pos = 5U;
    display_.add_display_data(stats_display, game_board_stats_height_pos, game_board_stats_width_pos);
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

// pushes player inventory on a display
void UI::pushInventoryOnDisplay(const common::Inventory& inventory) {
    const size_t inventory_display_height = 7U;
    const size_t inventory_display_width = 14U;
    CharDisplay inventory_display(inventory_display_height, inventory_display_width);
    inventory_display.fill_border();
    inventory_display.put_string("Inventory", 1U, 2U);
    inventory_display.put_line_hor(2U, 0U, inventory_display.width());

    std::unordered_map<common::ItemType, size_t> items;
    for (const auto& item : inventory) {
        items[item.itemType] += 1;
    }

    size_t inventory_line_idx = 3;
    for (const auto& [item_type, num_items] : items) {
        const auto item_type_str = std::string{style_->getGameItemRepr(item_type)};
        std::string inventory_item_str = std::to_string(num_items) + " " + item_type_str;

        inventory_display.put_string(inventory_item_str, inventory_line_idx, 4U);
        ++inventory_line_idx;
    }

    const size_t game_board_inventory_height_pos = 17U;
    const size_t game_board_inventory_width_pos = 35U;
    display_.add_display_data(inventory_display, game_board_inventory_height_pos, game_board_inventory_width_pos);
}

}  // namespace ui