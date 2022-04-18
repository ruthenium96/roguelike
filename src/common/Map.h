#pragma once

#include "Coordinate.h"
#include "ObjectType.h"

#include <map>
#include <vector>

namespace common {
    typedef std::map<common::Coordinate, std::vector<ObjectType>> Map;
}
