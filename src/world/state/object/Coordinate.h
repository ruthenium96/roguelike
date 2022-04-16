#ifndef ARCH_ROGUELIKE_COORDINATE_H
#define ARCH_ROGUELIKE_COORDINATE_H

#include <cstdint>

namespace world::state::object {
struct Coordinate {
    bool operator==(const Coordinate &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const Coordinate &rhs) const {
        return !(rhs == *this);
    }

    int32_t x = 0;
    int32_t y = 0;
};
}

#endif //ARCH_ROGUELIKE_COORDINATE_H
