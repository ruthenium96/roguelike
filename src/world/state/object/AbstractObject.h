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
class AbstractObject {
public:
    explicit AbstractObject(Identity&& identity) : identity_(identity) {};
    const Identity& getIdentity() const {
        return identity_;
    };
    const common::Coordinate& getCoordinate() const {
        return coordinate_;
    }
    common::Coordinate& getCoordinate() {
        return coordinate_;
    }
    virtual common::ObjectType getObjectType() const = 0;
//    virtual std::optional<std::any> getProperty();

private:
    const Identity identity_;
    common::Coordinate coordinate_;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTOBJECT_H
