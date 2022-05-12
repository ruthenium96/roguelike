#include "Observer.h"
#include <algorithm>
#include <stdexcept>
namespace world::state::object {

std::shared_ptr<object::AbstractObject> world::state::object::Observer::getPlayer() {
    return player_;
}

std::shared_ptr<const object::AbstractObject> Observer::getPlayer() const {
    return player_;
}

std::optional<std::shared_ptr<object::AbstractObject>> Observer::getObject(Identity identity) {
    if (identityObjectMap_.count(identity) == 0) {
        return std::nullopt;
    } else {
        return identityObjectMap_.at(identity);
    }
}

void Observer::addObject(const std::shared_ptr<object::AbstractObject>& object) {
    if (identityObjectMap_.find(object->getIdentity()) != identityObjectMap_.end()) {
        throw std::invalid_argument("Trying to add object with already existing Identity");
    }
    identityObjectMap_[object->getIdentity()] = object;
    if (object->getObjectType() == common::ObjectType::PLAYER) {
        if (player_ == nullptr) {
            player_ = object;
        } else {
            // TODO: throw something here
        }
    }
}

std::vector<std::shared_ptr<AbstractObject>> Observer::getObjectsAtCoordinate(common::Coordinate coordinate) const {
    std::vector<std::shared_ptr<AbstractObject>> answer;
    for (const auto& [_, object] : identityObjectMap_) {
        if (object->getCoordinate() == coordinate) {
            answer.push_back(object);
        }
    }
    return answer;
}

std::vector<std::shared_ptr<AbstractObject>> Observer::getAllObjects() const {
    std::vector<std::shared_ptr<AbstractObject>> objects;
    objects.reserve(identityObjectMap_.size());
    for (const auto& [_, object] : identityObjectMap_) {
        objects.push_back(object);
    }
    return objects;
}

void Observer::deleteObject(Identity identity) {
    identityObjectMap_.erase(identity);
}

bool Observer::operator==(const Observer &rhs) const {
    if (identityObjectMap_.size() != rhs.identityObjectMap_.size()) {
        return false;
    }
    auto liter = identityObjectMap_.begin();
    auto riter = rhs.identityObjectMap_.begin();
    while (liter != identityObjectMap_.end()) {
        if (liter->first != riter->first || *(liter->second) != *(riter->second)) {
            return false;
        }
        ++liter;
        ++riter;
    }
    return true;
}

bool Observer::operator!=(const Observer &rhs) const {
    return !(rhs == *this);
}

size_t Observer::howManyItemsOfThisTypeHoldsPlayer(common::ItemType type) const {
    size_t answer = 0;
    for (const auto& item : getPlayer()->getItems()) {
        if (item->getItemType() == type) {
            ++answer;
        }
    }
    return answer;
}

size_t Observer::countHowManyTimesItemIsWearedByPlayer(common::ItemType type) const {
    size_t answer = 0;
    auto player = getPlayer();
    if (player->getProperty("armor").has_value()) {
        auto wearedType = std::any_cast<common::ItemType>(player->getProperty("armor").value());
        if (type == wearedType) {
            ++answer;
        }
    }
    if (player->getProperty("leftHand").has_value()) {
        auto wearedType = std::any_cast<common::ItemType>(player->getProperty("leftHand").value());
        if (type == wearedType) {
            ++answer;
        }
    }
    if (player->getProperty("rightHand").has_value()) {
        auto wearedType = std::any_cast<common::ItemType>(player->getProperty("rightHand").value());
        if (type == wearedType) {
            ++answer;
        }
    }
    return answer;
}
}  // namespace world::state::object