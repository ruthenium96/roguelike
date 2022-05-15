#include "AbstractAction.h"
#include <stdexcept>
#include <utility>

namespace world::state::action {
void AbstractAction::deleteItselfFromActionObserver(action::Observer& actionObserver) {
    actionObserver.deleteAction(getSelfIdentity().value());
}

const std::optional<Identity>& AbstractAction::getSelfIdentity() const {
    return selfIdentity_;
}

const std::optional<Identity>& AbstractAction::getCorrespondingObjectIdentity() const {
    return correspondingObjectIdentity_;
}

void AbstractAction::setCorrespondingObjectIdentity(const std::optional<Identity>& correspondingObjectIdentity) {
    correspondingObjectIdentity_ = correspondingObjectIdentity;
}

const std::optional<Identity>& AbstractAction::getCorrespondingItemIdentity() const {
    return correspondingItemIdentity_;
}

void AbstractAction::setCorrespondingItemIdentity(const std::optional<Identity>& correspondingItemIdentity) {
    correspondingItemIdentity_ = correspondingItemIdentity;
}

bool AbstractAction::isEveryTurn() const {
    // every_turn can be false if something temporary turn it off, for example, confusing
    return getProperty("every_turn").has_value() && std::any_cast<bool>(getProperty("every_turn").value());
}

bool AbstractAction::operator==(const AbstractAction& rhs) const {
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

bool AbstractAction::operator!=(const AbstractAction& rhs) const {
    return !(rhs == *this);
}

void AbstractAction::attack(std::shared_ptr<object::AbstractObject>& attacker,
                            std::shared_ptr<object::AbstractObject>& defender) {
    auto attacker_attack = std::any_cast<int32_t>(attacker->getProperty("attack").value());
    auto defender_defence = std::any_cast<int32_t>(defender->getProperty("defence").value());

    int32_t damage = std::max(attacker_attack - defender_defence, 0);

    auto old_hp = std::any_cast<int32_t>(defender->getProperty("hp").value());
    defender->setProperty("hp", old_hp - damage);
}
}  // namespace world::state::action