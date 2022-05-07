#ifndef ARCH_ROGUELIKE_ABSTRACTACTION_H
#define ARCH_ROGUELIKE_ABSTRACTACTION_H

#include "../object/Observer.h"
#include "Observer.h"

namespace world::state::action {
class Observer;

// Abstract class of Action -- something that changes Objects or other Actions.
class AbstractAction {
  public:
    explicit AbstractAction(std::optional<Identity> selfIdentity) : selfIdentity_(selfIdentity){};
    // It is precondition: should this Action be applied or not.
    virtual bool precondition(const object::Observer&, const action::Observer&) = 0;

    // Changes Object and Actions of interest.
    virtual void changeTarget(object::Observer&, action::Observer&) = 0;

    // Should this action trying to apply every turn?
    // False by default.
    bool isEveryTurn() const;

    // Delete itself from set of Actions
    void deleteItselfFromActionObserver(action::Observer& actionObserver);

    const std::optional<Identity>& getSelfIdentity() const;

    const std::optional<Identity>& getCorrespondingObjectIdentity() const;
    void setCorrespondingObjectIdentity(const std::optional<Identity>& correspondingObjectIdentity);

    const std::optional<Identity>& getCorrespondingItemIdentity() const;
    void setCorrespondingItemIdentity(const std::optional<Identity>& correspondingItemIdentity);

    std::optional<std::any> getProperty(const std::string& property_name) const;
    void setProperty(const std::string& property_name, std::any value);
    const std::map<std::string, std::any>& getAllProperties() const;

    bool operator==(const AbstractAction &rhs) const;

    bool operator!=(const AbstractAction &rhs) const;

private:
    const std::optional<Identity> selfIdentity_;
    std::optional<Identity> correspondingObjectIdentity_;
    std::optional<Identity> correspondingItemIdentity_;
    std::map<std::string, std::any> property_;

    static bool compareTwoAny(const std::any& lhs, const std::any& rhs) ;
};

}  // namespace world::state::action

#endif  // ARCH_ROGUELIKE_ABSTRACTACTION_H
