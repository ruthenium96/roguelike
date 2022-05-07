#ifndef ARCH_ROGUELIKE_DESERIALIZER_H
#define ARCH_ROGUELIKE_DESERIALIZER_H

#include "ProtobufEngine.h"
#include <filesystem>

namespace world::generator::serialization {
class Deserializer {
public:
    Deserializer() = default;
    world::state::State deserialize(const ProtoSerializer::State& proto_state) const;
    world::state::State deserialize_from_stream(std::istream& stream) const;
    world::state::State deserialize_from_file(const std::filesystem::path& path) const;

private:
    ProtobufEngine engine_;


};
}

#endif //ARCH_ROGUELIKE_DESERIALIZER_H
