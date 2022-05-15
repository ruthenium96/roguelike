#include "game_object_style.h"
#include <algorithm>
#include <cassert>

namespace ui {

char DefaultStyle::getGameObjectsRepr(const std::vector<ObjectType>& objects) const {
    if (objects.empty()) {
        return ' ';
    }

    if (std::find(objects.cbegin(), objects.cend(), ObjectType::PLAYER) != objects.end()) {
        return getGameObjectRepr(ObjectType::PLAYER);
    }
    if (std::find(objects.cbegin(), objects.cend(), ObjectType::NPC) != objects.end()) {
        return getGameObjectRepr(ObjectType::NPC);
    }
    if (std::find(objects.cbegin(), objects.cend(), ObjectType::MOLD) != objects.end()) {
        return getGameObjectRepr(ObjectType::MOLD);
    }
    if (std::find(objects.cbegin(), objects.cend(), ObjectType::ARTEFACT) != objects.end()) {
        return getGameObjectRepr(ObjectType::ARTEFACT);
    }

    return getGameObjectRepr(objects.back());
}

char DefaultStyle::getGameObjectRepr(ObjectType type) const {
    return object_styles_.at(type);
}

char DefaultStyle::getGameItemRepr(ItemType type) const {
    return item_styles_.at(type);
}

}  // namespace ui
