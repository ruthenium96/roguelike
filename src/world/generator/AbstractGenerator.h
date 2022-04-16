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

struct ObjectAndActions {
    std::shared_ptr<state::object::AbstractObject> object;
    std::vector<std::shared_ptr<state::action::AbstractAction>> actions;
};

class AbstractGenerator {
public:
    virtual std::vector<ObjectAndActions> generateObjects(state::object::Coordinate, const state::object::Observer&) = 0;
    virtual ~AbstractGenerator() = default;;

private:
    // TODO: should we keep Coordinates of already generated Coordinates?
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
