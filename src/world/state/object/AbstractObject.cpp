#include "AbstractObject.h"

#include <stdexcept>
#include <cassert>

namespace world::state::object {

bool AbstractObject::operator==(const AbstractObject &rhs) const {
    if (std::tie(selfIdentity_, coordinate_) !=
    std::tie(rhs.selfIdentity_, rhs.coordinate_)) {
        return false;
    }

    if (items_.size() != rhs.items_.size()) {
        return false;
    }
    for (size_t i = 0; i < items_.size(); ++i) {
        if (*items_[i] != *rhs.items_[i]) {
            return false;
        }
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

bool AbstractObject::operator!=(const AbstractObject &rhs) const {
    return !(rhs == *this);
}

void AbstractObject::levelUp(int32_t dexp) {
    auto mbXp = getProperty("xp");
    auto mbLvl = getProperty("lvl");
    if (!mbXp.has_value() || !mbLvl.has_value()) {
        assert(0);
    }
    auto old_xp = std::any_cast<int32_t>(mbXp.value());
    auto old_lvl = std::any_cast<int32_t>(mbLvl.value());

    auto new_xp = old_xp + dexp;
    setProperty("xp", new_xp);

    int new_lvl = 0;
    uint32_t unew_xp = new_xp;
    while (unew_xp > 1) {
        unew_xp >>= 1;
        ++new_lvl;
    }
    setProperty("lvl", new_lvl);

    int32_t dlvl = new_lvl - old_lvl;
    auto old_attack = std::any_cast<int32_t>(getProperty("attack").value());
    auto old_defence = std::any_cast<int32_t>(getProperty("defence").value());

    setProperty("attack", old_attack + dlvl);
    setProperty("defence", old_defence + dlvl);

}
}  // namespace world::state::object