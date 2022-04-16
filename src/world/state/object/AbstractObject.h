#ifndef ARCH_ROGUELIKE_ABSTRACTOBJECT_H
#define ARCH_ROGUELIKE_ABSTRACTOBJECT_H

#include <cstdint>
#include <vector>
#include <optional>
#include <any>

#include "Identity.h"
#include "Coordinate.h"

namespace world::state::object {
class AbstractObject {
public:
    explicit AbstractObject(Identity&& identity) : identity_(identity) {};
    const Identity& getIdentity() const {
        return identity_;
    };
    const Coordinate& getCoordinate() const {
        return coordinate_;
    }
    Coordinate& getCoordinate() {
        return coordinate_;
    }
//    virtual std::optional<std::any> getProperty();

private:
    const Identity identity_;
    Coordinate coordinate_;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTOBJECT_H
