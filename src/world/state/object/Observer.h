#ifndef ARCH_ROGUELIKE_OBSERVER_H
#define ARCH_ROGUELIKE_OBSERVER_H

#include <map>
#include <memory>
#include <optional>
#include "Identity.h"
#include "AbstractObject.h"
#include "concrete/Player.h"

namespace world::state::object {
class Observer {
public:
    // TODO: change to object::Player
    std::shared_ptr<object::AbstractObject> getPlayer();
    std::optional<std::shared_ptr<object::AbstractObject>> getObject(Identity);
    void addObject(const std::shared_ptr<object::AbstractObject>&);

private:

    std::map<object::Identity, std::shared_ptr<object::AbstractObject>> identityObjectMap_;
};
}

#endif //ARCH_ROGUELIKE_OBSERVER_H
