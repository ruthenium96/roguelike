#include "Serializer.h"
#include <fstream>
#include <iostream>

namespace world::generator::serialization {
ProtoSerializer::State Serializer::serialize(const state::State& state) const {
    return engine_.serialize(state);
}

void Serializer::serialize_to_stream(const state::State& state, std::ostream& stream) const {
    auto proto_state = serialize(state);
    proto_state.SerializeToOstream(&stream);
}

void Serializer::serialize_to_file(const state::State& state, const std::filesystem::path& path) const {
    std::fstream file_stream(path.string(), std::ios::out | std::ios::trunc | std::ios::binary);
    serialize_to_stream(state, file_stream);
}

}  // namespace world::generator::serialization