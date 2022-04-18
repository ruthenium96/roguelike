#include "Controller.h"

#include <algorithm>

namespace controller 
{

void Controller::start() {
    auto map = engine_.getMap(); // NB: copying is here, change to vector_view?
    ui_.drawMap(map);  // TODO: ui_.draw(engine_ || world), controller should not know about what will be draw

    auto command = manager_.readCommand();  // while (manager_.read_command())
    while (command != common::ControllerCommand::EXIT) {
        if (command == common::ControllerCommand::UNKNOWN) {
            command = manager_.readCommand();
            continue;
        }
        // TODO: encapsulate clear in terminal ui
        engine_.applyCommand(command);
        map = engine_.getMap();
        ui_.drawMap(map);

        command = manager_.readCommand();  // move to while condition
    }
}

} // namespace controller 
