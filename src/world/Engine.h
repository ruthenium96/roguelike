#ifndef ARCH_ROGUELIKE_ENGINE_H
#define ARCH_ROGUELIKE_ENGINE_H

#include <memory>

#include "state/State.h"
#include "generator/AbstractGenerator.h"
#include "../common/Command.h"
#include "../common/Map.h"

namespace world {
// Engine corresponds for interaction of World with other modules.
class Engine {
public:
    Engine();
    // Applies ControllerCommand and returns common::Map.
    void applyCommand(const common::ControllerCommand&);
    // Generate current Map
    common::Map getMap();

private:
    void generateWorldAroundPlayer(common::Coordinate playerCoordinate);

    state::State state_;
    std::unique_ptr<generator::AbstractGenerator> generator_;
};
}

#endif //ARCH_ROGUELIKE_ENGINE_H
