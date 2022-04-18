#pragma once

#include "../ui/UI.h"
#include "../world/Engine.h"
#include "input/KeyboardManager.h"

namespace controller
{

class Controller {
public:
    Controller() = default;
    void start();
    void init() {
        // temp do nothing
    }
    void finalize() {
        // temp do nothing
    }
private:
    world::Engine engine_;
    ui::UI ui_;
    controller::input::KeyboardManager manager_;
};

} // namespace controller
