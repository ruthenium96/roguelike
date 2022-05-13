#include "Controller.h"
#include "../common/Command.h"
#include <algorithm>

namespace controller {
using common::Command;

namespace {

bool is_ui_command(const Command& command) {
    if (std::holds_alternative<common::Interact>(command)) {
        return true;
    } else if (std::holds_alternative<common::UI_DropItem>(command)) {
        return true;
    } else if (std::holds_alternative<common::Move>(command)) {
        return true;
    } else if (std::holds_alternative<common::Ignore>(command)) {
        return true;
    } else {
        return false;
    }
}

bool is_world_command(const Command& command) {
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

    Command command;
    auto worldUITransfer = engine_.getWorldUITransfer();
    ui_.draw(worldUITransfer);
    while (true) {
        command = manager_.readCommand();
        if (std::holds_alternative<common::Controller_Unknown>(command)) {
            continue;
        } else if (std::holds_alternative<common::Controller_Exit>(command)) {
            break;
        } else if (std::holds_alternative<common::Controller_ChangeRegime>(command)) {
            changeRegime(worldUITransfer);
            // reset command to ignore, it is the dirty trick
            command = common::Ignore();
        }

        // set "default" value
        common::Command engineCommand = common::Ignore();

        if (getCurrentRegime() == CurrentRegime::UI) {
            if (is_ui_command(command)) {
                auto UICommand = ui_.apply_command(command, worldUITransfer);
                engineCommand = engine_.applyCommand(UICommand);
            }
            // TODO: return to world regime if the last item was dropped
            // do nothing if it is not command of UI
        } else if (getCurrentRegime() == CurrentRegime::WORLD) {
            if (is_world_command(command)) {
                engineCommand = engine_.applyCommand(command);
            }
            // do nothing if it is not command of World
        } else {
            assert(0);
        }

        if (std::holds_alternative<common::WorldUITransfer>(engineCommand)) {
            worldUITransfer = std::get<common::WorldUITransfer>(engineCommand);
            ui_.draw(worldUITransfer);
            continue;
        }
        if (std::holds_alternative<common::Death>(engineCommand)) {
            auto death = std::get<common::Death>(engineCommand);
            ui_.drawDeath(death);

            Command afterDeathCommand = manager_.readCommand();
            if (std::holds_alternative<common::Controller_Exit>(afterDeathCommand)) {
                break;
            }

            engine_.resetWorld();
            worldUITransfer = engine_.getWorldUITransfer();
            if (getCurrentRegime() == CurrentRegime::UI) {
                changeRegime(worldUITransfer);
            }
            ui_.draw(worldUITransfer);
        }
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
