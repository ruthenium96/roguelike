add_library(game_engine
        GameEngine.cpp GameEngine.h
        world_state/WorldState.cpp world_state/WorldState.h
        world_generator/AbstractWorldGenerator.h
        world_state/game_object/AbstractObject.h
        world_state/game_object/Player.cpp world_state/game_object/Player.h
        )