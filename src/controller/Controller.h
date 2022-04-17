#pragma once

#include "../ui/UI.h"
#include "../world/Engine.h"
#include "input/AbstractManager.h"

namespace controller {
class Controller {
public:
    Controller() = default;
    void start();
private:
    world::Engine& engine_;
    ui::UI& ui_;
    controller::input::AbstractManager& manager_;
};
}
