#ifndef ARCH_ROGUELIKE_OBSERVER_H
#define ARCH_ROGUELIKE_OBSERVER_H

#include <map>
#include <memory>
#include <optional>
#include "Identity.h"
#include "AbstractObject.h"
#include "concrete/Player.h"
#include "../../../common/Map.h"

namespace world::state::object {
class Observer {
public:
    std::shared_ptr<object::Player> getPlayer();
    std::shared_ptr<const object::Player> getPlayer() const;
    std::optional<std::shared_ptr<object::AbstractObject>> getObject(Identity);

    std::vector<std::shared_ptr<AbstractObject>> getObjects(common::Coordinate) const;

    void addObject(const std::shared_ptr<object::AbstractObject>&);

private:

    std::map<object::Identity, std::shared_ptr<object::AbstractObject>> identityObjectMap_;
};
}

#endif //ARCH_ROGUELIKE_OBSERVER_H
