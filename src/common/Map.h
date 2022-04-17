#ifndef ARCH_ROGUELIKE_MAP_H
#define ARCH_ROGUELIKE_MAP_H

#include <vector>
#include "Coordinate.h"
#include "ObjectType.h"

namespace common {
    typedef std::map<common::Coordinate, std::vector<ObjectType>> Map;
}

#endif //ARCH_ROGUELIKE_MAP_H
