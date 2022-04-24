#include "Controller.h"
#include "../common/Command.h"
#include <algorithm>

namespace controller {

void Controller::start() {
    // use us_.draw_init();

    using common::ControllerCommand;

    ControllerCommand command;
    do {
        auto world_state = engine_.getWorldUITransfer();
        ui_.draw(world_state);

        command = manager_.readCommand();

        if (command == ControllerCommand::UNKNOWN || command == ControllerCommand::EXIT) {
            continue;
        }

        engine_.applyCommand(command);

    } while (command != ControllerCommand::EXIT);

    // us_.draw_final();
}

}  // namespace controller
