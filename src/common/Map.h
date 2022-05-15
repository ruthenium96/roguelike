#pragma once

#include "Coordinate.h"
#include "ObjectType.h"
#include <map>
#include <vector>

namespace common {

using Map = std::map<common::Coordinate, std::vector<ObjectType>>;

}  // namespace common
