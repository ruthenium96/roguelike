#include "Poison.h"

namespace world::state::action {

Poison::Poison(Identity selfIdentity, Identity objectIdentity, int32_t hp_decrease, int32_t duration) :
    AbstractAction(selfIdentity), objectIdentity_(objectIdentity), hp_decrease_(hp_decrease), duration_(duration) {
    everyTurn_ = true;
}

bool Poison::precondition(const object::Observer &observer, const Observer &observer1) {
    return true;
}

void Poison::changeTarget(object::Observer &objectObserver, action::Observer &actionObserver) {
    auto maybe_object = objectObserver.getObject(objectIdentity_);
    if (maybe_object.has_value()) {
        auto object = maybe_object.value();
        if (object->getProperty("hp").has_value()) {
            auto old_hp = std::any_cast<int32_t>(object->getProperty("hp").value());
            auto new_hp = std::make_any<int32_t>(old_hp - hp_decrease_);
            object->setProperty("hp", new_hp);
        }
    }
    --duration_;
    if (duration_ <= 0) {
        deleteItselfFromActionObserver(actionObserver);
    }
}
}