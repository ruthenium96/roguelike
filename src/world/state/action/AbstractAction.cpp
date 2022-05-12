#include "AbstractAction.h"

#include <stdexcept>
#include <utility>

namespace world::state::action {
void AbstractAction::deleteItselfFromActionObserver(action::Observer& actionObserver) {
    actionObserver.deleteAction(getSelfIdentity().value());
}

const std::optional<Identity> &AbstractAction::getSelfIdentity() const {
    return selfIdentity_;
}

const std::optional<Identity> &AbstractAction::getCorrespondingObjectIdentity() const {
    return correspondingObjectIdentity_;
}

void AbstractAction::setCorrespondingObjectIdentity(const std::optional<Identity> &correspondingObjectIdentity) {
    correspondingObjectIdentity_ = correspondingObjectIdentity;
}

const std::optional<Identity> &AbstractAction::getCorrespondingItemIdentity() const {
    return correspondingItemIdentity_;
}

void AbstractAction::setCorrespondingItemIdentity(const std::optional<Identity> &correspondingItemIdentity) {
    correspondingItemIdentity_ = correspondingItemIdentity;
}

bool AbstractAction::isEveryTurn() const {
    return getProperty("every_turn") != std::nullopt;
}

bool AbstractAction::operator==(const AbstractAction &rhs) const {
    if (std::tie(selfIdentity_, correspondingObjectIdentity_, correspondingItemIdentity_) !=
           std::tie(rhs.selfIdentity_, rhs.correspondingObjectIdentity_, rhs.correspondingItemIdentity_)) {
        return false;
    }

    if (getAllProperties().size() != rhs.getAllProperties().size()) {
        return false;
    }
    auto liter = getAllProperties().begin();
    auto riter = rhs.getAllProperties().begin();
    while (liter != getAllProperties().end()) {
        if (liter->first != riter->first) {
            return false;
        }
        if (!compareTwoAny(liter->second, riter->second)) {
            return false;
        }
        ++liter;
        ++riter;
    }

    return true;
}

bool AbstractAction::operator!=(const AbstractAction &rhs) const {
    return !(rhs == *this);
}
}  // namespace world::state::action