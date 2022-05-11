add_library(state
        State.cpp State.h
        Identity.h

        object/AbstractObject.cpp object/AbstractObject.h
        object/Observer.cpp object/Observer.h
        object/concrete/Player.cpp object/concrete/Player.h
        object/concrete/Floor.cpp object/concrete/Floor.h
        object/concrete/Wall.cpp object/concrete/Wall.h
        object/concrete/Artefact.cpp object/concrete/Artefact.h

        action/AbstractAction.h action/AbstractAction.cpp
        action/Observer.cpp action/Observer.h
        action/concrete/PlayerDrop.cpp action/concrete/PlayerDrop.h
        action/concrete/PlayerMove.cpp action/concrete/PlayerMove.h
        action/concrete/PlayerInteract.cpp action/concrete/PlayerInteract.h
        action/concrete/PlayerWearUnwear.cpp action/concrete/PlayerWearUnwear.h
        action/concrete/PickDropItem.cpp action/concrete/PickDropItem.h
        action/concrete/Poison.cpp action/concrete/Poison.h

        item/AbstractItem.cpp item/AbstractItem.h
        item/concrete/Stick.cpp item/concrete/Stick.h
        item/concrete/Ring.h
        )