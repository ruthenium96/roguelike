#pragma once  // TODO: use guards instead

#include "../common/ObjectType.h"
#include <unordered_map>
#include <vector>

namespace ui
{

// interface that provide styles for GameObjects when draw to UI
class IStyle
{
  protected:
    using ObjectType = common::ObjectType;

  public:
    virtual char getGameObjectsRepr(const std::vector<ObjectType>& objects) const = 0;

    // should be protected due to CppCoreGuidelines
    // BUT: not work with unique_ptr. Read!
    // protected:
    virtual ~IStyle() = default;
};

// Default Game Object style for ConsoleDisplay
// Uses simple chars
class DefaultStyle : public IStyle
{
  public:
    // get the char for the whole game objects on tile
    char getGameObjectsRepr(const std::vector<ObjectType>& objects) const override;

    // get the char for single game objects on tile
    char getGameObjectRepr(ObjectType type) const;

  private:
    // TODO: make static
    const std::unordered_map<common::ObjectType, char> object_styles_{{
        {ObjectType::PLAYER, 'P'},
        {ObjectType::FLOOR, '.'},
        {ObjectType::WALL, '#'},
        {ObjectType::ARTEFACT, 'I'},
    }};
};

}  // namespace ui
