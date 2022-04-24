#pragma once

#include "Coordinate.h"
#include "ObjectType.h"
#include <map>
#include <vector>

namespace common {

using Map = std::map<common::Coordinate, std::vector<ObjectType>>;

// TODO: refactor
// namespace
// {
// static constexpr size_t kDefaultMapHeight{21};
// static constexpr size_t kDefaultMapWidth{41};

// } // namespace

// class Map {
// public:
//     inline static constexpr size_t height{};
//     inline static constexpr size_t width{};

//     void set(size_t x, size_t y, std::vector<ObjectType>)

// private:
// std::map<common::Coordinate, std::vector<ObjectType>> data_;
// };

}  // namespace common
