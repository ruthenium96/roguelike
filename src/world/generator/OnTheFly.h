#ifndef ARCH_ROGUELIKE_ONTHEFLY_H
#define ARCH_ROGUELIKE_ONTHEFLY_H

#include "AbstractGenerator.h"

namespace world::generator {

class OnTheFly : public AbstractGenerator {
public:
    std::vector<ObjectAndActions> generateObjects(state::object::Coordinate, const state::object::Observer&) override;

private:
    uint32_t generated_objects_ = 0;

};
}

#endif //ARCH_ROGUELIKE_ONTHEFLY_H
