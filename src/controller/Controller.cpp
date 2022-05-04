#include "Controller.h"
#include "../common/Command.h"
#include <algorithm>

namespace controller {
using common::ControllerCommand;

namespace {

bool is_ui_command(const ControllerCommand& command) {
    switch (command) {
        case ControllerCommand::UI_ACTIVATE_INVENTORY:
        case ControllerCommand::UI_INVENTORY_DOWN:
        case ControllerCommand::UI_INVENTORY_UP:
        case ControllerCommand::UI_INVENTORY_APPLY:
            return true;
            break;
    }
    return false;
}

}  // namespace

void Controller::start() {
    // use us_.draw_init();

    ControllerCommand command;
    do {
        auto world_state = engine_.getWorldUITransfer();
        ui_.draw(world_state);

        command = manager_.readCommand();
        if (command == ControllerCommand::UNKNOWN || command == ControllerCommand::EXIT) {
            continue;
        }

        if (is_ui_command(command)) {
            ui_.apply_command(command, world_state);
            ui_.draw(world_state);
        } else {
            // move outside else block to process command returned from ui_
            ui_.deactivate_state();
            engine_.applyCommand(command);
        }

    } while (command != ControllerCommand::EXIT);

    // us_.draw_final();
}

}  // namespace controller
