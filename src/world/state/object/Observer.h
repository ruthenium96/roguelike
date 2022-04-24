#ifndef ARCH_ROGUELIKE_OBJECT_OBSERVER_H
#define ARCH_ROGUELIKE_OBJECT_OBSERVER_H

#include "../../../common/Map.h"
#include "../Identity.h"
#include "AbstractObject.h"
#include "concrete/Player.h"
#include <map>
#include <memory>
#include <optional>

namespace world::state::object {

// Helps to get Objects of interests.
class Observer {
  public:
    // Player getters:
    std::shared_ptr<object::Player> getPlayer();
    std::shared_ptr<const object::Player> getPlayer() const;
    // Get object using its Identity.
    std::optional<std::shared_ptr<object::AbstractObject>> getObject(Identity);

    // Get all Objects using their Coordinate.
    std::vector<std::shared_ptr<AbstractObject>> getObjectsAtCoordinate(common::Coordinate coordinate) const;
    std::vector<std::shared_ptr<AbstractObject>> getAllObjects() const;

    // Adds new object.
    void addObject(const std::shared_ptr<object::AbstractObject>&);
    //
    void deleteObject(Identity);

  private:
    std::map<Identity, std::shared_ptr<AbstractObject>> identityObjectMap_;
};

}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_OBJECT_OBSERVER_H
