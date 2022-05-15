#include "Poison.h"

namespace world::state::action {

Poison::Poison(std::optional<Identity> selfIdentity, int32_t hp_decrease, int32_t duration)
    : AbstractAction(selfIdentity) {
    setProperty("every_turn", std::make_any<bool>(true));
    setProperty("dhp", std::make_any<int32_t>(hp_decrease));
    setProperty("duration", std::make_any<int32_t>(duration));
}

bool Poison::precondition(const object::Observer& observer, const Observer& observer1) {
    return true;
}

void Poison::changeTarget(object::Observer& objectObserver, action::Observer& actionObserver) {
    auto maybe_object = objectObserver.getObject(getCorrespondingObjectIdentity().value());
    if (maybe_object.has_value()) {
        auto object = maybe_object.value();
        if (object->getProperty("hp").has_value()) {
            auto dhp = std::any_cast<int32_t>(getProperty("dhp").value());
            auto old_hp = std::any_cast<int32_t>(object->getProperty("hp").value());
            auto new_hp = std::make_any<int32_t>(old_hp + dhp);
            object->setProperty("hp", new_hp);
        }
    }
    auto duration = std::any_cast<int32_t>(getProperty("duration").value());
    --duration;
    setProperty("duration", std::make_any<int32_t>(duration));
    if (duration <= 0) {
        deleteItselfFromActionObserver(actionObserver);
    }
}

Poison::Poison(std::optional<Identity> selfIdentity) : Poison(selfIdentity, 0, 0) {}

ActionType Poison::getActionType() const {
    return ActionType::POISON;
}
}  // namespace world::state::action