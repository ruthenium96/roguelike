#ifndef ARCH_ROGUELIKE_ENGINE_H
#define ARCH_ROGUELIKE_ENGINE_H

#include <memory>

#include "state/State.h"
#include "generator/AbstractGenerator.h"
#include "../common/Command.h"
#include "../common/Map.h"

namespace world {
class Engine {
public:
    Engine();
    //common::Map
    common::Map applyCommand(const common::ControllerCommand&);

private:
    common::Map generateMap();
    void generateWorldAroundPlayer(common::Coordinate playerCoordinate);

    state::State state_;
    std::unique_ptr<generator::AbstractGenerator> generator_;
};
}

#endif //ARCH_ROGUELIKE_ENGINE_H
