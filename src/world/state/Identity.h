#ifndef ARCH_ROGUELIKE_IDENTITY_H
#define ARCH_ROGUELIKE_IDENTITY_H

#include <cstdint>

namespace world::state {
// Identity of Objects, Actions and Items
class Identity {
  public:
    explicit Identity(uint64_t identity) : identity_(identity){};
    Identity() = delete;
    // TODO: Can we delete it? It necessary because we keep two copies of Identity.
    Identity(const Identity&) = default;
    Identity& operator=(const Identity&) = default;
    Identity(Identity&&) = default;
    Identity& operator=(Identity&&) = default;

    uint64_t asNumber() const {return identity_;};

    bool operator==(const Identity& rhs) const { return identity_ == rhs.identity_; }

    bool operator!=(const Identity& rhs) const { return !(rhs == *this); }

    bool operator<(const Identity& rhs) const { return identity_ < rhs.identity_; }

    bool operator>(const Identity& rhs) const { return rhs < *this; }

    bool operator<=(const Identity& rhs) const { return !(rhs < *this); }

    bool operator>=(const Identity& rhs) const { return !(*this < rhs); };

  private:
    uint64_t identity_;
};

// Static class for generating Identities.
class IdentityGenerator {
public:
    static Identity getNewIdentity() {
        return Identity(generatedIdentities++);
    };
    static void setTo(uint64_t newValue) {
        generatedIdentities = newValue;
    }
private:
    inline static uint64_t generatedIdentities;
};


}  // namespace world::state

#endif  // ARCH_ROGUELIKE_IDENTITY_H
