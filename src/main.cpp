#include "world/Engine.h"
#include <iostream>
#include <algorithm>
#include "common/Command.h"

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
    world::Engine engine;

    while (true) {
        char azaza;
        std::cin >> azaza;
        if (azaza == 'Q') {
            break;
        }
        if (azaza == 'W' || azaza == 'A' || azaza == 'S' || azaza == 'D') {
            common::Command command;
            if (azaza == 'W') {
                command.inputCommand = common::InputCommand::MOVE_TOP;
            } else if (azaza == 'A') {
                command.inputCommand = common::InputCommand::MOVE_LEFT;
            } else if (azaza == 'S') {
                command.inputCommand = common::InputCommand::MOVE_BOTTOM;
            } else if (azaza == 'D') {
                command.inputCommand = common::InputCommand::MOVE_RIGHT;
            }
            auto map = engine.applyCommand(command);
            drawMap(map);
        } else {
            continue;
        }
    }

    return 0;
}