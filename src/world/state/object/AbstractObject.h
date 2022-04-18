#ifndef ARCH_ROGUELIKE_ABSTRACTOBJECT_H
#define ARCH_ROGUELIKE_ABSTRACTOBJECT_H

#include <cstdint>
#include <vector>
#include <optional>
#include <any>

#include "Identity.h"
#include "../../../common/Coordinate.h"
#include "../../../common/ObjectType.h"

namespace world::state::object {
// An abstract class for all Objects. Object is something, that always have the Coordinate.
class AbstractObject {
public:
    explicit AbstractObject(Identity&& identity) : identity_(std::move(identity)) {};
    // Identity getter.
    const Identity& getIdentity() const {
        return identity_;
    };
    // Coordinate getters.
    const common::Coordinate& getCoordinate() const {
        return coordinate_;
    }
    common::Coordinate& getCoordinate() {
        return coordinate_;
    }
    // ObjectType getter.
    virtual common::ObjectType getObjectType() const = 0;
//    virtual std::optional<std::any> getProperty();

private:
    const Identity identity_;
    common::Coordinate coordinate_;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTOBJECT_H
