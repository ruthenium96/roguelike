#include "Controller.h"
#include "../common/Command.h"
#include <algorithm>

namespace controller {
using common::ControllerCommand;

namespace {

bool is_ui_command(const ControllerCommand& command) {
    if (std::holds_alternative<common::Interact>(command)) {
        return true;
    } else if (std::holds_alternative<common::UI_DropItem>(command)) {
        return true;
    } else if (std::holds_alternative<common::Move>(command)) {
        return true;
    } else {
        return false;
    }
}

bool is_world_command(const ControllerCommand& command) {
    if (std::holds_alternative<common::Move>(command)) {
        return true;
    } else if (std::holds_alternative<common::Interact>(command)) {
        return true;
    } else if (std::holds_alternative<common::World_ApplyItem>(command)) {
        return true;
    } else if (std::holds_alternative<common::World_DropItem>(command)) {
        return true;
    } else if (std::holds_alternative<common::Ignore>(command)) {
        return true;
    } else {
        return false;
    }
}

}  // namespace

void Controller::start() {
    // use us_.draw_init();

    ControllerCommand command;
    auto world_state = engine_.getWorldUITransfer();
    ui_.draw(world_state);
    while (true) {
        command = manager_.readCommand();
        if (std::holds_alternative<common::Controller_Unknown>(command)) {
            continue;
        } else if (std::holds_alternative<common::Controller_Exit>(command)) {
            break;
        } else if (std::holds_alternative<common::Controller_ChangeRegime>(command)) {
            changeRegime(world_state);
        }

        if (getCurrentRegime() == CurrentRegime::UI) {
            if (is_ui_command(command)) {
                auto commandFromUI = ui_.apply_command(command, world_state);
                engine_.applyCommand(commandFromUI);
            }
            // TODO: return to world regime if the last item was dropped
            // do nothing if it is not command of UI
        } else if (getCurrentRegime() == CurrentRegime::WORLD) {
            if (is_world_command(command)) {
                engine_.applyCommand(command);
            }
            // do nothing if it is not command of World
        } else {
            assert(0);
        }

        world_state = engine_.getWorldUITransfer();
        ui_.draw(world_state);
    }

    // us_.draw_final();
}

void Controller::changeRegime(const common::WorldUITransfer& world_state) {
    if (currentRegime_ == CurrentRegime::WORLD) {
        if (ui_.activate_state(world_state)) {
            currentRegime_ = CurrentRegime::UI;
        }
    } else if (currentRegime_ == CurrentRegime::UI) {
        currentRegime_ = CurrentRegime::WORLD;
        ui_.deactivate_state(world_state);
    } else {
        assert(0);
    }

}

const Controller::CurrentRegime &Controller::getCurrentRegime() const {
    return currentRegime_;
}

}  // namespace controller
