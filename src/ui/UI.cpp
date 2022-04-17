#include "UI.h"

#include <iostream>
#include <map>
#include <algorithm>

namespace ui {


void UI::drawMap(const common::Map& map) {
    auto initial_coordinate = map.begin()->first;
    for (const auto& [coordinate, types] : map) {
        if (coordinate.y != initial_coordinate.y) {
            std::cout << std::endl;
            initial_coordinate = coordinate;
        }
        if (std::find(types.begin(), types.end(), common::ObjectType::PLAYER) != types.end()) {
            std::cout << getRepresentation(common::ObjectType::PLAYER);
        } else if (types.size() == 1) {
            std::cout << getRepresentation(types[0]);
        } else if (types.empty()) {
            std::cout << " ";
        } else {
            throw std::length_error("Something strange");
        }
    }
    std::cout << std::endl;
}

char UI::getRepresentation(const common::ObjectType& type) const {
    std::map<common::ObjectType, char> objToSymbolRepresentation = {{common::ObjectType::PLAYER, 'P'},
                                                                    {common::ObjectType::FLOOR, '.'},
                                                                    {common::ObjectType::WALL, '#'},};
    return objToSymbolRepresentation[type];
}
}