#ifndef ARCH_ROGUELIKE_ARTEFACT_H
#define ARCH_ROGUELIKE_ARTEFACT_H

#include "../AbstractObject.h"

namespace world::state::object {

class Artefact : public AbstractObject {
  public:
    explicit Artefact(const Identity& identity) : AbstractObject(identity) {
        // TODO: can we have static container with this names?
        // set artefact "interactable"
        property_["interactable"] = std::make_any<bool>(true);
    };

    common::ObjectType getObjectType() const override;

  private:
};

}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_ARTEFACT_H
