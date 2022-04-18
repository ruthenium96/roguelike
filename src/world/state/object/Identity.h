#ifndef ARCH_ROGUELIKE_IDENTITY_H
#define ARCH_ROGUELIKE_IDENTITY_H

#include <cstdint>

namespace world::state::object {
class Identity {
public:
    explicit Identity(uint32_t identity) : identity_(identity) {};
    Identity() = delete;
    // TODO: Can we delete it? It necessary because we keep two copies of Identity.
    Identity(const Identity&) = default;
    Identity& operator=(const Identity&) = delete;
    Identity(Identity&&) = default;
    Identity& operator=(Identity&&) = delete;

    bool operator==(const Identity &rhs) const {
        return identity_ == rhs.identity_;
    }

    bool operator!=(const Identity &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Identity &rhs) const {
        return identity_ < rhs.identity_;
    }

    bool operator>(const Identity &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Identity &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Identity &rhs) const {
        return !(*this < rhs);
    };
private:
    const uint32_t identity_;
};
}

#endif //ARCH_ROGUELIKE_IDENTITY_H
