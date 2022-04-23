#ifndef ARCH_ROGUELIKE_ABSTRACTACTION_H
#define ARCH_ROGUELIKE_ABSTRACTACTION_H

#include "../object/Observer.h"
#include "Observer.h"

namespace world::state::action
{
class Observer;

// Abstract class of Action -- something that changes Objects or other Actions.
class AbstractAction {
  public:
    explicit AbstractAction(std::optional<Identity> selfIdentity) : selfIdentity_(selfIdentity){};
    // It is precondition: should this Action be applied or not.
    virtual bool precondition(const object::Observer&, const action::Observer&) = 0;

    // Changes Object and Actions of interest.
    virtual void changeTarget(object::Observer&, action::Observer &) = 0;

    // Delete itself from set of Actions
    void deleteItselfFromActionObserver(action::Observer& actionObserver);

    const std::optional<Identity>& getSelfIdentity() const { return selfIdentity_; }

    const std::optional<Identity>& getCorrespondingObjectIdentity() const { return correspondingObjectIdentity_; }
    void setCorrespondingObjectIdentity(const std::optional<Identity>& correspondingObjectIdentity) {
        correspondingObjectIdentity_ = correspondingObjectIdentity;
    }

    const std::optional<Identity>& getCorrespondingItemIdentity() const { return correspondingItemIdentity_; }
    void setCorrespondingItemIdentity(const std::optional<Identity>& correspondingItemIdentity) {
        correspondingItemIdentity_ = correspondingItemIdentity;
    }

  private:
    const std::optional<Identity> selfIdentity_;
    std::optional<Identity> correspondingObjectIdentity_;
    std::optional<Identity> correspondingItemIdentity_;
};

}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_ABSTRACTACTION_H
