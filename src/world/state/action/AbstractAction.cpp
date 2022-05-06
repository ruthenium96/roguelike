#include "AbstractAction.h"

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

std::optional<std::any> AbstractAction::getProperty(const std::string &property_name) const {
    if (property_.count(property_name) == 0) {
        return std::nullopt;
    } else {
        return property_.at(property_name);
    }
}

void AbstractAction::setProperty(const std::string &property_name, std::any value) {
    property_[property_name] = std::move(value);
}

bool AbstractAction::isEveryTurn() const {
    return getProperty("every_turn") != std::nullopt;
}

const std::map<std::string, std::any> &AbstractAction::getAllProperties() const {
    return property_;
}
}  // namespace world::state::action