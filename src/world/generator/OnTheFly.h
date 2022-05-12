#ifndef ARCH_ROGUELIKE_ONTHEFLY_H
#define ARCH_ROGUELIKE_ONTHEFLY_H

#include "AbstractGenerator.h"
#include <set>
#include <random>

namespace world::generator {

// On the fly implementation of AbstractGenerator, uses random generation
class OnTheFly : public AbstractGenerator {
  public:
    OnTheFly();

    std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) override;

  private:
    uint64_t generated_identities_ = 0;
    // TODO: reimplement as unordered_set by implementing hash function
    std::set<common::Coordinate> generated_coordinates_;
    std::default_random_engine randomEngine_;
    std::uniform_real_distribution<float> distribution_;

};

}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_ONTHEFLY_H
