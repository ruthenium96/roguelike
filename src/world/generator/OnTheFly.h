#ifndef ARCH_ROGUELIKE_ONTHEFLY_H
#define ARCH_ROGUELIKE_ONTHEFLY_H

#include <set>
#include "AbstractGenerator.h"

namespace world::generator
{

// On the fly implementation of AbstractGenerator, uses random generation
class OnTheFly : public AbstractGenerator {
public:
    std::vector<ObjectAndActions> generateObjects(common::Coordinate, const state::object::Observer&) override;

private:
    uint32_t generated_objects_ = 0;
    // TODO: reimplement as unordered_set by implementing hash function
    std::set<common::Coordinate> generated_coordinates_;

};

} // namespace world::generator

#endif // ARCH_ROGUELIKE_ONTHEFLY_H
