#include "serialization.h"
#include "../../state/item/concrete/Stick.h"
#include "../../state/item/concrete/Ring.h"
#include "../../state/object/concrete/Artefact.h"
#include "../../state/object/concrete/Floor.h"
#include "../../state/object/concrete/Wall.h"
#include <fstream>
#include <memory>

void Serializer::associate_item_types() {
    item_mapper_.associate_types(ProtoSerializer::Item::STICK, common::ItemType::STICK);
    item_mapper_.associate_types(ProtoSerializer::Item::RING, common::ItemType::RING);
}

void Serializer::associate_object_types() {
    object_mapper_.associate_types(ProtoSerializer::Object::PLAYER, common::ObjectType::PLAYER);
    object_mapper_.associate_types(ProtoSerializer::Object::ARTEFACT, common::ObjectType::ARTEFACT);
    object_mapper_.associate_types(ProtoSerializer::Object::FLOOR, common::ObjectType::FLOOR);
    object_mapper_.associate_types(ProtoSerializer::Object::WALL, common::ObjectType::WALL);
}

Serializer::Serializer(const std::filesystem::path& path) : path_(path) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    associate_item_types();
    associate_object_types();
}

void Serializer::serialize(const world::state::State& state) {
    ProtoSerializer::State proto_state;

    // Serialize all Objects...
    for (const auto& object_ptr : state.getObjectObserver().getAllObjects()) {
        ProtoSerializer::Object* new_proto_object = proto_state.add_objects();
        // identity:
        new_proto_object->set_selfidentity(object_ptr->getIdentity().asNumber());
        // type:
        ProtoSerializer::Object::ObjectType object_proto_type =
                object_mapper_.get_proto_associated_type_with(object_ptr->getObjectType());
        new_proto_object->set_type(object_proto_type);
        // coordinate:
        common::Coordinate coords = object_ptr->getCoordinate();
        auto* proto_coords = new_proto_object->mutable_coords();
        proto_coords->set_x(coords.x);
        proto_coords->set_y(coords.y);
        new_proto_object->set_allocated_coords(proto_coords);
        // properties:
        auto* proto_properties = new_proto_object->mutable_properties();
        for (const auto& [key, value] : object_ptr->getAllProperties()) {
            if (key == "hp") {
                proto_properties->set_hp(std::any_cast<int32_t>(value));
            } else if (key == "xp") {
                proto_properties->set_xp(std::any_cast<int32_t>(value));
            } else if (key == "lvl") {
                proto_properties->set_lvl(std::any_cast<int32_t>(value));
            } else if (key == "blocking") {
                proto_properties->set_blocking(std::any_cast<bool>(value));
            } else if (key == "interactable") {
                proto_properties->set_interactable(std::any_cast<bool>(value));
            } else {
                throw std::invalid_argument("Unknown key");
            }
        }
        new_proto_object->set_allocated_properties(proto_properties);

        // ... and their Items
        for (const auto& item_ptr : object_ptr->getItems()) {
            ProtoSerializer::Item::ItemType item_proto_type =
                    item_mapper_.get_proto_associated_type_with(item_ptr->getItemType());
            ProtoSerializer::Item* new_proto_item = new_proto_object->add_items();
            new_proto_item->set_type(item_proto_type);
            new_proto_item->set_self_id(item_ptr->getSelfIdentity().asNumber());
            new_proto_item->set_owner_id(item_ptr->getObjectHolderIdentity().asNumber());
        }
    }
    // Serialize all Actions
    for (const auto& action_ptr : state.getActionObserver().)


    for (auto& object_ptr : observer.getAllObjects()) {
        ProtoSerializer::Object::ObjectType proto_type =
            object_mapper_.get_proto_associated_type_with(object_ptr->getObjectType());
        ProtoSerializer::Object* new_proto_object = proto_state.add_objects();
        new_proto_object->set_type(proto_type);
        auto map = new_proto_object->mutable_properties();
        //new_proto_object->mutable_properties()->insert(object_ptr->getAllProperties().cbegin(), object_ptr->getAllProperties().cend());

        common::Coordinate coords = object_ptr->getCoordinate();

        auto* proto_coords = new_proto_object->mutable_coords();
        proto_coords->set_x(coords.x);
        proto_coords->set_y(coords.y);

        new_proto_object->set_allocated_coords(proto_coords);
    }
    std::fstream serialize_stream(path_.string(), std::ios::out | std::ios::trunc | std::ios::binary);
    proto_state.SerializeToOstream(&serialize_stream);
}

world::state::State Serializer::deserialize() {
//    world::state::object::Observer observer;
//    std::fstream deserialize_stream(path_.string(), std::ios::in | std::ios::binary);
//    ProtoSerializer::State proto_state;
//    proto_state.ParseFromIstream(&deserialize_stream);
//
//    uint64_t identity_start = 0;
//
//    int objects_size = proto_state.objects_size();
//
//    for (int index = 0; index < objects_size; ++index) {
//        const ProtoSerializer::Object& proto_object = proto_state.objects(index);
//        common::ObjectType game_object_type = object_mapper_.get_game_associated_type_with(proto_object.type());
//
//        std::shared_ptr<world::state::object::AbstractObject> shared_object;
//        world::state::Identity identity(identity_start + index);
//        if (game_object_type == common::ObjectType::ARTEFACT) {
//            shared_object = std::make_shared<world::state::object::Artefact>(identity);
//        } else if (game_object_type == common::ObjectType::WALL) {
//            shared_object = std::make_shared<world::state::object::Wall>(identity);
//        } else if (game_object_type == common::ObjectType::FLOOR) {
//            shared_object = std::make_shared<world::state::object::Floor>(identity);
//        } else {
//            throw std::runtime_error("handle unknown object type during deserialization");
//        }
//        shared_object->getCoordinate().x = proto_object.coords().x();
//        shared_object->getCoordinate().y = proto_object.coords().y();
//        observer.addObject(shared_object);
//    }
//
//    identity_start += objects_size;
//    auto player = std::make_shared<world::state::object::Player>(world::state::Identity{++identity_start});
//
//    auto& items = player->getItems();
//    int items_size = proto_state.items_size();
//    for (int index = 0; index < items_size; ++index) {
//        const ProtoSerializer::Item& item_proto = proto_state.items(index);
//        common::ItemType game_item_type = item_mapper_.get_game_associated_type_with(item_proto.type());
//        world::state::Identity item_identity{++identity_start};
//        world::state::Identity object_identity{++identity_start};
//        if (game_item_type == common::ItemType::STICK) {
//            items.push_back(std::make_unique<world::state::item::Stick>(item_identity, object_identity));
//        } else if (game_item_type == common::ItemType::RING) {
//            items.push_back(std::make_unique<world::state::item::Ring>(item_identity, object_identity));
//        } else {
//            throw std::runtime_error("handle unknown object type during deserialization");
//        }
//    }
//    return observer;
}
