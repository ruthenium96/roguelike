#include "Controller.h"

#include <algorithm>

namespace controller {


void Controller::start() {
    system("clear");
    auto map = engine_.getMap();
    ui_.drawMap(map);
    auto command = manager_.readCommand();
    while (command != common::ControllerCommand::EXIT) {
        if (command == common::ControllerCommand::UNKNOWN) {
            command = manager_.readCommand();
            continue;
        }
        // TODO: encapsulate clear in terminal ui
        engine_.applyCommand(command);
        system("clear");
        map = engine_.getMap();
        ui_.drawMap(map);

        command = manager_.readCommand();
    }
}

}
