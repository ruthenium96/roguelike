#ifndef ARCH_ROGUELIKE_COORDINATE_H
#define ARCH_ROGUELIKE_COORDINATE_H

#include <cstdint>
#include <tuple>

namespace common {

// Coordinate of Object.
struct Coordinate {
    bool operator==(const Coordinate& rhs) const { return x == rhs.x && y == rhs.y; }

    bool operator!=(const Coordinate& rhs) const { return !(rhs == *this); }

    // At first, comparing vertical, then horizontal component
    // I guess, it can help to UI
    bool operator<(const Coordinate& rhs) const { return std::tie(y, x) < std::tie(rhs.y, rhs.x); }

    bool operator>(const Coordinate& rhs) const { return rhs < *this; }

    bool operator<=(const Coordinate& rhs) const { return !(rhs < *this); }

    bool operator>=(const Coordinate& rhs) const { return !(*this < rhs); }

    int32_t x = 0;
    int32_t y = 0;
};

}  // namespace common

#endif  // ARCH_ROGUELIKE_COORDINATE_H
