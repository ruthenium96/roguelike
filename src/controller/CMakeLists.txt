add_library(controller
        Controller.cpp Controller.h
        input/AbstractManager.cpp input/AbstractManager.h
        input/KeyboardManager.cpp input/KeyboardManager.h
        )

target_link_libraries(controller common)