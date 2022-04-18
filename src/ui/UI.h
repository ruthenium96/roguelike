#ifndef ARCH_ROGUELIKE_UI_H
#define ARCH_ROGUELIKE_UI_H

#include "../common/Map.h"


namespace ui {
class UI {
public:
    void drawMap(const common::Map& map);
private:
    // TODO: Should be moved to children of AbstractUI - ConsoleUI or TerminalUI
    char getRepresentation(const common::ObjectType& type) const;

};
}

#endif //ARCH_ROGUELIKE_UI_H
