#pragma once

// This class helps modules communicate each other.
namespace common
{

enum class ControllerCommand
{
    UNKNOWN,
    MOVE_TOP,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_BOTTOM,
    INTERACT,
    EXIT
};

}  // namespace common
