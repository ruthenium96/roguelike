#pragma once  // TODO: use guards instead

#include "../ui/UI.h"
#include "../world/Engine.h"
#include "input/KeyboardManager.h"

namespace controller {

class Controller {
  public:
    Controller() = default;

    // provide the main game loop
    void start();

    // prints initial game logo and keys
    void init() {
        // stub
    }

    // prints final game logo and stats
    void finalize() {
        // stub
    }

  private:
    world::Engine engine_;
    ui::UI ui_;
    controller::input::KeyboardManager manager_;
};

}  // namespace controller
