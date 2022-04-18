# pragma once // TODO: use guards instead

#include "../common/ObjectType.h"
#include <unordered_map>
#include <algorithm>


namespace ui 
{

class IStyle {
public:
    virtual char getGameObjectsRepr(
        const std::vector<common::ObjectType>& objects) const = 0;

// protected: // TODO: read about using protected dtor with unique_ptr
    virtual ~IStyle() = default;
};

class DefaultStyle : public IStyle{
public:

    char getGameObjectsRepr(
        const std::vector<common::ObjectType>& objects) const override
    {
        using common::ObjectType;

        if (std::find(objects.cbegin(), objects.cend(),
                      ObjectType::PLAYER) != objects.end())
        {
            return getGameObjectRepr(ObjectType::PLAYER);
        }

        return getGameObjectRepr(objects.back());
    }


    char getGameObjectRepr(common::ObjectType type) const {
        return object_styles_.at(type);
    }

private:
    // make static
    const std::unordered_map<common::ObjectType, char> object_styles_{{
        {common::ObjectType::PLAYER, 'P'},
        {common::ObjectType::FLOOR,  '.'},
        {common::ObjectType::WALL,   '#'},
    }};

};

} // namespace ui 


