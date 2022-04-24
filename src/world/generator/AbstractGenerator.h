#ifndef ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
#define ARCH_ROGUELIKE_ABSTRACTGENERATOR_H

#include "../state/action/AbstractAction.h"
#include "../state/object/AbstractObject.h"
#include "../state/object/Observer.h"
#include "../state/object/concrete/Floor.h"
#include "../state/object/concrete/Player.h"
#include <memory>
#include <vector>

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

  protected:
    void addPlayer(common::Coordinate, std::vector<ObjectAndActions>&, uint64_t&);
    void addFloor(common::Coordinate, std::vector<ObjectAndActions>&, uint64_t&);
    void addWall(common::Coordinate, std::vector<ObjectAndActions>&, uint64_t&);
    void addArtefact(common::Coordinate, std::vector<ObjectAndActions>&, uint64_t&);
};

}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
