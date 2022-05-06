#ifndef ARCH_ROGUELIKE_ABSTRACTOBJECT_H
#define ARCH_ROGUELIKE_ABSTRACTOBJECT_H

#include "../../../common/Coordinate.h"
#include "../../../common/ObjectType.h"
#include "../Identity.h"
#include "../item/AbstractItem.h"
#include <any>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace world::state::object {
// An abstract class for all Objects. Object is something, that always have the Coordinate.
class AbstractObject {
  public:
    explicit AbstractObject(const Identity& identity) : selfIdentity_(identity){};
    // Identity getter.
    const Identity& getIdentity() const { return selfIdentity_; };
    // Coordinate getters.
    const common::Coordinate& getCoordinate() const { return coordinate_; }
    common::Coordinate& getCoordinate() { return coordinate_; }
    // ObjectType getter.
    virtual common::ObjectType getObjectType() const = 0;
    // Items getters:
    std::vector<std::unique_ptr<item::AbstractItem>>& getItems() { return items_; }
    const std::vector<std::unique_ptr<item::AbstractItem>>& getItems() const { return items_; }
    std::optional<std::any> getProperty(const std::string& property_name) const;
    void setProperty(const std::string& property_name, std::any value);

    virtual ~AbstractObject() = default;

  private:
    const Identity selfIdentity_;
    common::Coordinate coordinate_;
    // TODO: Can be replaced by std::vector<Identity>
    std::vector<std::unique_ptr<item::AbstractItem>> items_;
    std::map<std::string, std::any> property_;
};
}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_ABSTRACTOBJECT_H
