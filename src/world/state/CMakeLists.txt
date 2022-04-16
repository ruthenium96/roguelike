add_library(state
        State.cpp State.h
        object/AbstractObject.cpp object/AbstractObject.h
        object/concrete/Player.cpp object/concrete/Player.h
        action/AbstractAction.h
        object/Identity.h
        object/Coordinate.h
        object/concrete/Floor.cpp object/concrete/Floor.h
        action/concrete/PlayerMove.cpp action/concrete/PlayerMove.h
        object/Observer.cpp object/Observer.h
        )