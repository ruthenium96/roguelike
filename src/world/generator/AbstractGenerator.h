#ifndef ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
#define ARCH_ROGUELIKE_ABSTRACTGENERATOR_H

#include <memory>
#include <vector>
#include "../state/object/AbstractObject.h"
#include "../state/action/AbstractAction.h"
#include "../state/object/concrete/Player.h"
#include "../state/object/concrete/Floor.h"
#include "../state/object/Observer.h"

namespace world::generator {
// Suitable return type for generateObjects(), it has Object and its Actions.
struct ObjectAndActions {
    std::shared_ptr<state::object::AbstractObject> object;
    std::vector<std::shared_ptr<state::action::AbstractAction>> actions;
};

// An abstract class for generation of the World.
class AbstractGenerator {
public:
    // Generate Objects in Coordinate based on object::Observer information
    virtual std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) = 0;
    virtual ~AbstractGenerator() = default;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
