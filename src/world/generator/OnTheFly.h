#ifndef ARCH_ROGUELIKE_ONTHEFLY_H
#define ARCH_ROGUELIKE_ONTHEFLY_H

#include "AbstractGenerator.h"
#include <set>

namespace world::generator {
// On the fly implementation of AbstractGenerator, uses random generation
class OnTheFly : public AbstractGenerator {
  public:
    std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) override;

  private:
    // TODO: reimplement as unordered_set by implementing hash function
    std::set<common::Coordinate> generated_coordinates_;
    std::array<float, 1> wallProbability_ = {0.05};
    // Artefact, NPC and Mold probabilities
    std::array<float, 3> objectOnFloorProbability_ = {0.99, 0.985, 0.9825};

    friend GeneratorBuilder;
};

}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_ONTHEFLY_H
