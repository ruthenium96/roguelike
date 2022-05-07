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

bool AbstractAction::operator==(const AbstractAction &rhs) const {
    if (std::tie(selfIdentity_, correspondingObjectIdentity_, correspondingItemIdentity_) !=
           std::tie(rhs.selfIdentity_, rhs.correspondingObjectIdentity_, rhs.correspondingItemIdentity_)) {
        return false;
    }

    if (property_.size() != rhs.property_.size()) {
        return false;
    }
    auto liter = property_.begin();
    auto riter = rhs.property_.begin();
    while (liter != property_.end()) {
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

bool AbstractAction::compareTwoAny(const std::any& lhs, const std::any& rhs) {
    if (lhs.type() != rhs.type()) {
        return false;
    }
    if (lhs.type() == typeid(bool)) {
        return std::any_cast<bool>(lhs) == std::any_cast<bool>(rhs);
    }
    if (lhs.type() == typeid(uint64_t)) {
        return std::any_cast<uint64_t>(lhs) == std::any_cast<uint64_t>(rhs);
    }
    if (lhs.type() == typeid(int32_t)) {
        return std::any_cast<int32_t>(lhs) == std::any_cast<int32_t>(rhs);
    }
    throw std::invalid_argument("Unimplemented type for any comparison");
}
}  // namespace world::state::action