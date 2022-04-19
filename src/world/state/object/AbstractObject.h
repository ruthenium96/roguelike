#ifndef ARCH_ROGUELIKE_ABSTRACTOBJECT_H
#define ARCH_ROGUELIKE_ABSTRACTOBJECT_H

#include <cstdint>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <optional>
#include <any>

#include "../Identity.h"
#include "../item/AbstractItem.h"
#include "../../../common/Coordinate.h"
#include "../../../common/ObjectType.h"

namespace world::state::object {
// An abstract class for all Objects. Object is something, that always have the Coordinate.
class AbstractObject {
public:
    explicit AbstractObject(Identity&& identity) : identity_(identity) {};
    explicit AbstractObject(const Identity& identity) : identity_(identity) {};
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
    // Items getters:
    std::vector<std::unique_ptr<item::AbstractItem>>& getItems() {
        return items_;
    }
    const std::vector<std::unique_ptr<item::AbstractItem>>& getItems() const {
        return items_;
    }
    std::optional<std::any> getProperty(const std::string& property_name) const {
        if (property_.count(property_name) == 0) {
            return std::nullopt;
        } else {
            return property_.at(property_name);
        }
    };

private:
    const Identity identity_;
    common::Coordinate coordinate_;
    std::vector<std::unique_ptr<item::AbstractItem>> items_;
protected:
    std::map<std::string, std::any> property_;
};
}

#endif //ARCH_ROGUELIKE_ABSTRACTOBJECT_H
