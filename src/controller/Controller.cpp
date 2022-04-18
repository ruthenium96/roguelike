#include "Controller.h"

#include <algorithm>

namespace controller {


void Controller::start() {
    auto command = manager_.readCommand();
    while (command != common::ControllerCommand::EXIT) {
        // TODO: encapsulate clear in terminal ui
        system("clear");
        auto map = engine_.applyCommand(command);
        ui_.drawMap(map);
        command = manager_.readCommand();
    }
}

}
