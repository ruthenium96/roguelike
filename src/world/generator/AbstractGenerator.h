#ifndef ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
#define ARCH_ROGUELIKE_ABSTRACTGENERATOR_H

#include "../state/Identity.h"
#include "../state/action/AbstractAction.h"
#include "../state/object/AbstractObject.h"
#include "../state/object/Observer.h"
#include "../state/object/concrete/Floor.h"
#include "../state/object/concrete/Player.h"
#include "serialization/Serializer.h"
#include <memory>
#include <vector>

namespace world::generator {

// Suitable return type for generateObjects(), it has Object and its Actions.
struct ObjectAndActions {
    std::shared_ptr<state::object::AbstractObject> object;
    std::vector<std::shared_ptr<state::action::AbstractAction>> actions;
};
class GeneratorBuilder;

// An abstract class for generation of the World.
class AbstractGenerator {
  public:
    // Generate Objects in Coordinate based on object::Observer information
    virtual std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) = 0;
    virtual ~AbstractGenerator() = default;
    // returns reference to serializer
    const serialization::Serializer& getSaver() const;

  protected:
    void addPlayer(common::Coordinate, std::vector<ObjectAndActions>&);
    void addFloor(common::Coordinate, std::vector<ObjectAndActions>&);
    void addWall(common::Coordinate, std::vector<ObjectAndActions>&);
    void addArtefact(common::Coordinate, std::vector<ObjectAndActions>&);
    void addArtefact(common::Coordinate, std::vector<ObjectAndActions>&, std::array<float, 1> threshold);
    void addNPC(common::Coordinate, std::vector<ObjectAndActions>&);
    void addNPC(common::Coordinate, std::vector<ObjectAndActions>&, std::array<float, 2> threshold);
    void addMold(common::Coordinate, std::vector<ObjectAndActions>&);

  private:
    serialization::Serializer saver_;
    std::array<float, 1> artefactTypeProbability_ = {0.8};
    std::array<float, 2> NPCTypeProbability_ = {0.5, 0.1};

    friend GeneratorBuilder;
};

}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_ABSTRACTGENERATOR_H
