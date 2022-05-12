add_library(common
        Command.h
        Map.h
        ObjectType.h
        Coordinate.h
        WorldUITransfer.h
        PlayerMetrics.h
        Inventory.h
        ItemType.h
        PlayerEquipment.h)

set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)