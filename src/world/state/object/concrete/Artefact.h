#ifndef ARCH_ROGUELIKE_ARTEFACT_H
#define ARCH_ROGUELIKE_ARTEFACT_H

#include "../AbstractObject.h"

namespace world::state::object {

class Artefact : public AbstractObject {
  public:
    explicit Artefact(const Identity& identity);
    ;

    common::ObjectType getObjectType() const override;

  private:
};

}  // namespace world::state::object

#endif  // ARCH_ROGUELIKE_ARTEFACT_H
