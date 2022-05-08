add_library(state
        State.cpp State.h
        object/AbstractObject.cpp object/AbstractObject.h
        object/concrete/Player.cpp object/concrete/Player.h
        action/AbstractAction.h action/AbstractAction.cpp
        Identity.h
        object/concrete/Floor.cpp object/concrete/Floor.h
        action/concrete/PlayerMove.cpp action/concrete/PlayerMove.h
        object/Observer.cpp object/Observer.h
        object/concrete/Wall.cpp object/concrete/Wall.h
        object/concrete/Artefact.cpp object/concrete/Artefact.h
        item/AbstractItem.cpp item/AbstractItem.h
        item/concrete/Stick.cpp item/concrete/Stick.h
        action/concrete/PlayerInteract.cpp action/concrete/PlayerInteract.h
        action/concrete/PickDropItem.cpp action/concrete/PickDropItem.h
        action/Observer.cpp action/Observer.h
        action/concrete/Poison.cpp action/concrete/Poison.h)