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
    std::shared_ptr<object::AbstractObject> getPlayer();
    std::shared_ptr<const object::AbstractObject> getPlayer() const;
    // Get object using its Identity.
    std::optional<std::shared_ptr<object::AbstractObject>> getObject(Identity) const;

    // Get all Objects using their Coordinate.
    std::vector<std::shared_ptr<AbstractObject>> getObjectsAtCoordinate(common::Coordinate coordinate) const;
    std::vector<std::shared_ptr<AbstractObject>> getAllObjects() const;

    // Adds new object.
    void addObject(const std::shared_ptr<object::AbstractObject>&);
    //
    void deleteObject(Identity);


    size_t howManyItemsOfThisTypeHoldsPlayer(common::ItemType type) const;
    size_t countHowManyTimesItemIsWearedByPlayer(common::ItemType type) const;

    bool operator==(const Observer &rhs) const;
    bool operator!=(const Observer &rhs) const;

  private:
    std::map<Identity, std::shared_ptr<AbstractObject>> identityObjectMap_;
    std::shared_ptr<object::AbstractObject> player_ = nullptr;
};

}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_OBJECT_OBSERVER_H
