#ifndef ARCH_ROGUELIKE_ABSTRACTWORLDGENERATOR_H
#define ARCH_ROGUELIKE_ABSTRACTWORLDGENERATOR_H

#include <vector>
#include "../world_state/game_object/AbstractObject.h"

namespace game_engine::world_generator {
class AbstractWorldGenerator {
public:
    // TODO: take as parameters Coordinate and Map
    virtual std::vector<AbstractObject> generateObjects() = 0;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTWORLDGENERATOR_H
