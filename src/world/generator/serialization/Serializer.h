#ifndef ARCH_ROGUELIKE_SERIALIZER_H
#define ARCH_ROGUELIKE_SERIALIZER_H

#include "ProtobufEngine.h"
#include <filesystem>

namespace world::generator::serialization {
class Serializer {
public:
    Serializer() = default;

    ProtoSerializer::State serialize(const world::state::State& state) const;
    void serialize_to_stream(const world::state::State& state, std::ostream& stream) const;
    void serialize_to_file(const world::state::State& state, const std::filesystem::path& path) const;

private:
    ProtobufEngine engine_;
};
}

#endif //ARCH_ROGUELIKE_SERIALIZER_H
