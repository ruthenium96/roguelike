#ifndef ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
#define ARCH_ROGUELIKE_ABSTRACTGENERATOR_H

#include "../state/action/AbstractAction.h"
#include "../state/object/AbstractObject.h"
#include "../state/object/Observer.h"
#include "../state/object/concrete/Floor.h"
#include "../state/object/concrete/Player.h"
#include "../state/Identity.h"
#include "serialization/Serializer.h"
#include <memory>
#include <random>
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
    AbstractGenerator();

    // Generate Objects in Coordinate based on object::Observer information
    virtual std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) = 0;
    virtual ~AbstractGenerator() = default;
    const serialization::Serializer& getSaver() const;

  protected:
    void addPlayer(common::Coordinate, std::vector<ObjectAndActions>&);
    void addFloor(common::Coordinate, std::vector<ObjectAndActions>&);
    void addWall(common::Coordinate, std::vector<ObjectAndActions>&);
    void addArtefact(common::Coordinate, std::vector<ObjectAndActions>&);
    void addArtefact(common::Coordinate, std::vector<ObjectAndActions>&, std::array<float, 1> threshold);
    void addNPC(common::Coordinate, std::vector<ObjectAndActions>&);
    void addNPC(common::Coordinate, std::vector<ObjectAndActions>&, std::array<float, 2> threshold);
    std::default_random_engine randomEngine_;
    std::uniform_real_distribution<float> distribution_;


  private:
    serialization::Serializer saver_;
};

}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
