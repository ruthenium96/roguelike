#include "UI.h"

#include <iostream>
#include <map>
#include <algorithm>

#include <string>

namespace ui
{

UI::UI(const world::Engine& engine)
    : engine_{engine}
{
    style_ = std::make_unique<DefaultStyle>();
}

void UI::draw() const {
    pushStatsOnDisplay(engine_.getStats());
    pushMapOnDisplay(engine_.getMap());
    display_.draw();
}


void UI::pushStatsOnDisplay(int32_t) const {
    std::string stats_str {
     "Hello in Arch Roguelike 3000! "
     "Level:1   HP:100%   Mana:100%   Exp:47%"};
    
    for (size_t i = 0; i != stats_str.size(); ++i) {
      constexpr auto kFirstLineIdx{0U};
      display_.at(kFirstLineIdx, i) = stats_str[i];
    }
}

void UI::pushMapOnDisplay(const common::Map& map) const {
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
        }
        else {
            width_i++;
        }
    }
}



} // namespace ui