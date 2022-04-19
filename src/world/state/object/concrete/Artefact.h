#ifndef ARCH_ROGUELIKE_ARTEFACT_H
#define ARCH_ROGUELIKE_ARTEFACT_H

#include "../AbstractObject.h"

namespace world::state::object {

class Artefact : public AbstractObject {
public:
    explicit Artefact(Identity&& identity) : AbstractObject(identity) {};
    explicit Artefact(const Identity& identity) : AbstractObject(identity) {};


    common::ObjectType getObjectType() const override;
private:
    void initialize() {
        // TODO: can we have static container with this names?
        // set artefact "interactable"
        property_["interactable"] = std::make_any<bool>(true);
    }
};

}

#endif //ARCH_ROGUELIKE_ARTEFACT_H
