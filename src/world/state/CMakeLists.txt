add_library(state
        State.cpp State.h
        Identity.h
        Entity.cpp Entity.h

        object/AbstractObject.cpp object/AbstractObject.h
        object/Observer.cpp object/Observer.h
        object/concrete/Player.cpp object/concrete/Player.h
        object/concrete/Floor.cpp object/concrete/Floor.h
        object/concrete/Wall.cpp object/concrete/Wall.h
        object/concrete/Artefact.cpp object/concrete/Artefact.h
        object/concrete/NPC.cpp object/concrete/NPC.h
        object/concrete/Mold.cpp object/concrete/Mold.h

        action/ActionType.h
        action/AbstractAction.h action/AbstractAction.cpp
        action/Observer.cpp action/Observer.h
        action/instant/PlayerDrop.cpp action/instant/PlayerDrop.h
        action/instant/Move.cpp action/instant/Move.h
        action/instant/PlayerWorldInteract.cpp action/instant/PlayerWorldInteract.h
        action/instant/PlayerUIInteract.cpp action/instant/PlayerUIInteract.h
        action/internal/PickDropItem.cpp action/internal/PickDropItem.h
        action/internal/Poison.cpp action/internal/Poison.h
        action/internal/Confuse.cpp action/internal/Confuse.h
        action/npc/AbstractNPC.cpp action/npc/AbstractNPC.h
        action/npc/CowardNPC.cpp action/npc/CowardNPC.h
        action/npc/AggressiveNPC.cpp action/npc/AggressiveNPC.h
        action/npc/InactiveNPC.cpp action/npc/InactiveNPC.h

        item/AbstractItem.cpp item/AbstractItem.h
        item/concrete/Stick.cpp item/concrete/Stick.h
        item/concrete/Ring.cpp item/concrete/Ring.h
        )

target_link_libraries(state random)