#include "game_object_style.h"
#include <algorithm>

namespace ui
{

char DefaultStyle::getGameObjectsRepr(const std::vector<ObjectType>& objects) const
{
    if (std::find(objects.cbegin(), objects.cend(), ObjectType::PLAYER) != objects.end())
    {
        return getGameObjectRepr(ObjectType::PLAYER);
    }

    return getGameObjectRepr(objects.back());
}

char DefaultStyle::getGameObjectRepr(ObjectType type) const
{
    return object_styles_.at(type);
}

}  // namespace ui
