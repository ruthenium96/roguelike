#include "world/Engine.h"
#include <iostream>
#include <algorithm>
#include "common/Command.h"
#include "controller/Controller.h"

static std::map<common::ObjectType, char> ui = {{common::PLAYER, 'P'},
                                                {common::FLOOR, '.'},
                                                {common::WALL, '#'},};

void drawMap(common::Map map) {
    auto initial_coordinate = map.begin()->first;
    for (const auto& [coordinate, types] : map) {
        if (coordinate.y != initial_coordinate.y) {
            std::cout << std::endl;
            initial_coordinate = coordinate;
        }
        if (std::find(types.begin(), types.end(), common::PLAYER) != types.end()) {
            std::cout << ui[common::PLAYER];
        } else if (types.size() == 1) {
            std::cout << ui[types[0]];
        } else if (types.empty()) {
            std::cout << " ";
        } else {
            throw std::length_error("Something strange");
        }
    }
    std::cout << std::endl;
}

int main() {
    controller::Controller controller;
    controller.start();

    return 0;
}