#include "Controller.h"
#include "../common/Command.h"
#include <algorithm>

namespace controller {
using common::ControllerCommand;

namespace {

bool is_ui_command(const ControllerCommand& command) {
    if (std::holds_alternative<common::NonparameterizedVariant>(command)) {
        auto variant = std::get<common::NonparameterizedVariant>(command);
        switch (variant) {
            case common::NonparameterizedVariant::UI_ACTIVATE_INVENTORY:
            case common::NonparameterizedVariant::UI_INVENTORY_APPLY:
            case common::NonparameterizedVariant::UI_INVENTORY_DROP:
                return true;
                break;
            default:
                return false;
                break;
        }
    } else if (std::holds_alternative<common::UiMoveInventory>(command)) {
        return true;
    } else {
        return false;
    }
}

}  // namespace

void Controller::start() {
    // use us_.draw_init();

    ControllerCommand command;
    do {
        auto world_state = engine_.getWorldUITransfer();
        ui_.draw(world_state);

        command = manager_.readCommand();
        if (std::holds_alternative<common::NonparameterizedVariant>(command)) {
            auto variant = std::get<common::NonparameterizedVariant>(command);
            if (variant == common::NonparameterizedVariant::UNKNOWN) {
                continue;
            }
            if (variant == common::NonparameterizedVariant::EXIT) {
                break;
            }
        }

        if (is_ui_command(command)) {
            command = ui_.apply_command(command, world_state);
            ui_.draw(world_state);
        } else {
            // move outside else block to process command returned from ui_
            ui_.deactivate_state();
        }

        engine_.applyCommand(command);

    } while (true);

    // us_.draw_final();
}

}  // namespace controller
