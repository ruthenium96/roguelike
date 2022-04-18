# pragma once // TODO: use guards instead

#include "../common/ObjectType.h"
#include <unordered_map>
#include <algorithm>


namespace ui 
{

class IStyle {
protected:
    using ObjectType = common::ObjectType;
public:
    virtual char getGameObjectsRepr(
        const std::vector<ObjectType>& objects) const = 0;

// should be protected due to CppCoreGuidelines
// BUT: not work with unique_ptr. Read!
// protected: 
    virtual ~IStyle() = default;
};


class DefaultStyle : public IStyle{
public:
    char getGameObjectsRepr(
        const std::vector<ObjectType>& objects) const override;
        
    char getGameObjectRepr(ObjectType type) const;

private:
    // TODO: make static
    const std::unordered_map<common::ObjectType, char> object_styles_{{
        {ObjectType::PLAYER, 'P'},
        {ObjectType::FLOOR,  '.'},
        {ObjectType::WALL,   '#'},
    }};

};

} // namespace ui 


