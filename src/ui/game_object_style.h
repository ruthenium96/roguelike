# pragma once // TODO: use guards instead

#include "../common/ObjectType.h"
#include <unordered_map>
#include <map>

namespace ui 
{

class IStyle {
public:
    virtual char getGameObjectRepr(common::ObjectType type) const = 0;
// protected: // TODO: read about using protected dtor with unique_ptr
    virtual ~IStyle() = default;
};

class DefaultStyle : public IStyle{
public:
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


