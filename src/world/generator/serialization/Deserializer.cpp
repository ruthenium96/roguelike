#include "Deserializer.h"
#include <fstream>
#include <iostream>

namespace world::generator::serialization {

world::state::State Deserializer::deserialize(const ProtoSerializer::State& proto_state) const {
    return engine_.deserialize(proto_state);
}

world::state::State Deserializer::deserialize_from_stream(std::istream& stream) const {
    ProtoSerializer::State proto_state;
    proto_state.ParseFromIstream(&stream);
    return deserialize(proto_state);
}

world::state::State Deserializer::deserialize_from_file(const std::filesystem::path& path) const {
    std::fstream stream(path.string(), std::ios::in | std::ios::binary);
    return deserialize_from_stream(stream);
}
}  // namespace world::generator::serialization