#ifndef ARCH_ROGUELIKE_ONTHEFLY_H
#define ARCH_ROGUELIKE_ONTHEFLY_H

#include "AbstractGenerator.h"
#include <set>

namespace world::generator
{

// On the fly implementation of AbstractGenerator, uses random generation
class OnTheFly : public AbstractGenerator
{
  public:
    std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) override;

  private:
    void addPlayer(common::Coordinate, std::vector<ObjectAndActions>&);
    void addFloor(common::Coordinate, std::vector<ObjectAndActions>&);
    void addWall(common::Coordinate, std::vector<ObjectAndActions>&);
    void addArtefact(common::Coordinate, std::vector<ObjectAndActions>&);
    uint64_t generated_identities_ = 0;
    // TODO: reimplement as unordered_set by implementing hash function
    std::set<common::Coordinate> generated_coordinates_;
};

}  // namespace world::generator

#endif  // ARCH_ROGUELIKE_ONTHEFLY_H
