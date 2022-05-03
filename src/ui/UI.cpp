#include "UI.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

namespace ui {

UI::UI(const std::string& style) {
    if (style == "default") {
        style_ = std::make_unique<DefaultStyle>();
    } else {
        throw std::runtime_error("Style " + style + " is not implemented in UI.");
    }
}

void UI::draw(const common::WorldUITransfer& world_state) {
    pushStatsOnDisplay(world_state.playerMetrics);
    pushMapOnDisplay(world_state.map);
    pushInventoryOnDisplay(world_state.inventory);
    display_.draw();
}

void UI::pushStatsOnDisplay(const common::PlayerMetrics& player_stats) {
    std::string stats_str{
        "Hello in Arch Roguelike 3000! "
        "Level:1   HP:100%   Mana:100%   Exp:47%"};

    for (size_t i = 0; i != stats_str.size(); ++i) {
        constexpr auto kFirstLineIdx{0U};
        display_.at(kFirstLineIdx, i) = stats_str[i];
    }
}

void UI::pushMapOnDisplay(const common::Map& map) {
    auto initial_coordinate = map.begin()->first;
    auto width_i = 0U;
    auto height_i = 1U;

    for (const auto& [coordinate, objects] : map) {
        // currently only the last object is painted
        display_.at(height_i, width_i) = style_->getGameObjectsRepr(objects);

        if (coordinate.y != initial_coordinate.y) {
            width_i = 0U;
            ++height_i;
            initial_coordinate = coordinate;
        } else {
            width_i++;
        }
    }
}

// pushes player inventory on a display
void UI::pushInventoryOnDisplay(const common::Inventory& inventory) {}

}  // namespace ui