#ifndef ARCH_ROGUELIKE_PROTOBUFENGINE_H
#define ARCH_ROGUELIKE_PROTOBUFENGINE_H

#include "proto/state.pb.h"
#include "../../state/State.h"
#include "../../state/object/AbstractObject.h"
#include <map>
#include <unordered_map>
#include <utility>

namespace {
template <class ProtoType, class GameType>
class ProtoToGameTypeMapper {
  public:
    ProtoType get_proto_associated_type_with(GameType type) const { return gameToProto.at(type); }

    GameType get_game_associated_type_with(ProtoType type) const { return protoToGame.at(type); }

    void associate_types(ProtoType proto_type, GameType game_type) {
        protoToGame[proto_type] = game_type;
        gameToProto[game_type] = proto_type;
    }

  private:
    std::unordered_map<ProtoType, GameType> protoToGame;
    std::unordered_map<GameType, ProtoType> gameToProto;
};
}  // namespace

namespace world::generator::serialization {
class ProtobufEngine {
  public:
    ProtobufEngine();
    ProtoSerializer::State serialize(const world::state::State& state) const;
    world::state::State deserialize(const ProtoSerializer::State& proto_state) const;

  private:
    void associate_item_types();
    void associate_object_types();
    ProtoToGameTypeMapper<ProtoSerializer::Item::ItemType, common::ItemType> item_mapper_;
    ProtoToGameTypeMapper<ProtoSerializer::Object::ObjectType, common::ObjectType> object_mapper_;

    std::map<common::ObjectType, std::function<std::shared_ptr<world::state::object::AbstractObject>(world::state::Identity)>> objectConstructor_;
};
}
#endif  // ARCH_ROGUELIKE_PROTOBUFENGINE_H
