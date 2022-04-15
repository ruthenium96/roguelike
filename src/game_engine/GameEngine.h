#ifndef ARCH_ROGUELIKE_GAMEENGINE_H
#define ARCH_ROGUELIKE_GAMEENGINE_H

#include <memory>

#include "world_state/WorldState.h"
#include "world_generator/AbstractWorldGenerator.h"

namespace game_engine {
class GameEngine {
public:
    GameEngine() = default;

private:
    world_state::WorldState worldState_;
    std::unique_ptr<world_generator::AbstractWorldGenerator> worldGenerator_;
};
}

#endif //ARCH_ROGUELIKE_GAMEENGINE_H
