#ifndef ARCH_ROGUELIKE_SERIALIZATION_H
#define ARCH_ROGUELIKE_SERIALIZATION_H

#include <filesystem>
#include <utility>
#include <unordered_map>

#include "proto/state.pb.h"

#include "../../world/state/object/Observer.h"

namespace {
template <class ProtoType, class GameType>
class ProtoToGameTypeMapper {
public:
    ProtoType get_proto_associated_type_with(GameType type) {
        return gameToProto[type];
    }

    GameType get_game_associated_type_with(ProtoType type) {
        return protoToGame[type];
    }

    void associate_types(ProtoType proto_type, GameType game_type) {
        protoToGame[proto_type] = game_type;
        gameToProto[game_type] = proto_type;
    }

private:
    std::unordered_map<ProtoType, GameType> protoToGame;
    std::unordered_map<GameType, ProtoType> gameToProto;
};
}

class Serializer {
public:
    explicit Serializer(const std::filesystem::path& path);

    void serialize(const world::state::object::Observer& observer);
    world::state::object::Observer deserialize();
private:
    void associate_item_types();
    void associate_object_types();
    ProtoToGameTypeMapper<ProtoSerializer::Item::ItemType, common::ItemType> item_mapper_;
    ProtoToGameTypeMapper<ProtoSerializer::Object::ObjectType, common::ObjectType> object_mapper_;
    std::filesystem::path path_;
};

#endif //ARCH_ROGUELIKE_SERIALIZATION_H
