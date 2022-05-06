#include "serialization.h"
#include "../../state/action/concrete/PickItem.h"
#include "../../state/action/concrete/Poison.h"
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
                proto_properties->mutable_hp()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "xp") {
                proto_properties->mutable_xp()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "lvl") {
                proto_properties->mutable_lvl()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "blocking") {
                proto_properties->mutable_blocking()->set_value(std::any_cast<bool>(value));
            } else if (key == "interactable") {
                proto_properties->mutable_interactable()->set_value(std::any_cast<bool>(value));
            } else {
                throw std::invalid_argument("Unknown key: " + key);
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
    for (const auto& action_ptr : state.getActionObserver().getAllActions()) {
        ProtoSerializer::Action* new_proto_action = proto_state.add_actions();
        // self-Identity:
        if (action_ptr->getSelfIdentity().has_value()) {
            new_proto_action->set_selfidentity(action_ptr->getSelfIdentity().value().asNumber());
        }
        // Object Identity:
        if (action_ptr->getCorrespondingObjectIdentity().has_value()) {
            new_proto_action->set_objectidentity(action_ptr->getCorrespondingObjectIdentity().value().asNumber());
        }
        // Item Identity:
        if (action_ptr->getCorrespondingItemIdentity().has_value()) {
            new_proto_action->set_itemidentity(action_ptr->getCorrespondingItemIdentity().value().asNumber());
        }
        // properties:
        auto* proto_properties = new_proto_action->mutable_properties();
        for (const auto& [key, value] : action_ptr->getAllProperties()) {
            if (key == "dx") {
                proto_properties->set_dx(std::any_cast<int32_t>(value));
            } else if (key == "dy") {
                proto_properties->set_dy(std::any_cast<int32_t>(value));
            } else if (key == "dhp") {
                proto_properties->set_dhp(std::any_cast<int32_t>(value));
            } else if (key == "duration") {
                proto_properties->set_duration(std::any_cast<int32_t>(value));
            } else if (key == "every_turn") {
                proto_properties->set_every_turn(std::any_cast<bool>(value));
            } else {
                throw std::invalid_argument("Unknown key: " + key);
            }
        }
        new_proto_action->set_allocated_properties(proto_properties);
    }
    std::fstream serialize_stream(path_.string(), std::ios::out | std::ios::trunc | std::ios::binary);
    proto_state.SerializeToOstream(&serialize_stream);
}

world::state::State Serializer::deserialize() {
    world::state::State state;
    std::fstream deserialize_stream(path_.string(), std::ios::in | std::ios::binary);
    ProtoSerializer::State proto_state;
    proto_state.ParseFromIstream(&deserialize_stream);

    // Objects and Items
    int objects_size = proto_state.objects_size();
    for (int index = 0; index < objects_size; ++index) {
        const ProtoSerializer::Object& proto_object = proto_state.objects(index);
        common::ObjectType game_object_type = object_mapper_.get_game_associated_type_with(proto_object.type());

        // type and identity
        std::shared_ptr<world::state::object::AbstractObject> shared_object;
        auto objectIdentity = world::state::Identity(proto_object.selfidentity());
        if (game_object_type == common::ObjectType::PLAYER) {
            shared_object = std::make_shared<world::state::object::Player>(objectIdentity);
        } else if (game_object_type == common::ObjectType::ARTEFACT) {
            shared_object = std::make_shared<world::state::object::Artefact>(objectIdentity);
        } else if (game_object_type == common::ObjectType::WALL) {
            shared_object = std::make_shared<world::state::object::Wall>(objectIdentity);
        } else if (game_object_type == common::ObjectType::FLOOR) {
            shared_object = std::make_shared<world::state::object::Floor>(objectIdentity);
        } else {
            throw std::runtime_error("handle unknown object type during deserialization");
        }
        // coordinates
        shared_object->getCoordinate().x = proto_object.coords().x();
        shared_object->getCoordinate().y = proto_object.coords().y();
        // properties
        if (proto_object.properties().has_hp()) {
            shared_object->setProperty("hp", proto_object.properties().hp().value());
        }
        if (proto_object.properties().has_xp()) {
            shared_object->setProperty("xp", proto_object.properties().xp().value());
        }
        if (proto_object.properties().has_lvl()) {
            shared_object->setProperty("lvl", proto_object.properties().lvl().value());
        }
        if (proto_object.properties().has_blocking()) {
            shared_object->setProperty("blocking", proto_object.properties().blocking().value());
        }
        if (proto_object.properties().has_interactable()) {
            shared_object->setProperty("interactable", proto_object.properties().interactable().value());
        }
        // items
        int items_size = proto_object.items_size();
        for (int item_index = 0; item_index < items_size; ++item_index) {
            const ProtoSerializer::Item& item_proto = proto_object.items(index);
            common::ItemType game_item_type = item_mapper_.get_game_associated_type_with(item_proto.type());
            auto itemIdentity = world::state::Identity(item_proto.self_id());
            auto ownerIdentity = world::state::Identity(item_proto.owner_id());
            if (game_item_type == common::ItemType::STICK) {
                shared_object->getItems().push_back(std::make_unique<world::state::item::Stick>(itemIdentity, ownerIdentity));
            } else if (game_item_type == common::ItemType::RING) {
                shared_object->getItems().push_back(std::make_unique<world::state::item::Ring>(itemIdentity, ownerIdentity));
            } else {
                throw std::runtime_error("handle unknown item type during deserialization");
            }
        }
        state.getObjectObserver().addObject(shared_object);
    }
    // actions
    int actions_size = proto_state.actions_size();
    for (int action_index = 0; action_index < actions_size; ++action_index) {
        const ProtoSerializer::Action& proto_action = proto_state.actions(action_index);
        // type, identity
        auto action_type = proto_action.type();
        std::shared_ptr<world::state::action::AbstractAction> shared_action;
        auto actionIdentity = world::state::Identity(proto_action.selfidentity());
        if (action_type == ProtoSerializer::Action_ActionType_PICKITEM) {
            shared_action = std::make_shared<world::state::action::PickItem>(actionIdentity);
        } else if (action_type == ProtoSerializer::Action_ActionType_POISON) {
            shared_action = std::make_shared<world::state::action::Poison>(actionIdentity);
        } else {
            throw std::runtime_error("handle unknown action type during deserialization");
        }
        // object identity:
        if (proto_action.has_objectidentity()) {
            auto objectIdentity = world::state::Identity(proto_action.objectidentity().value());
            shared_action->setCorrespondingObjectIdentity(objectIdentity);
        }
        // item identity:
        if (proto_action.has_itemidentity()) {
            auto itemIdentity = world::state::Identity(proto_action.itemidentity().value());
            shared_action->setCorrespondingItemIdentity(itemIdentity);
        }
        // properties:
        if (proto_action.properties().has_dx()) {
            shared_action->setProperty("dx", proto_action.properties().dx().value());
        }
        if (proto_action.properties().has_dy()) {
            shared_action->setProperty("dy", proto_action.properties().dy().value());
        }
        if (proto_action.properties().has_dhp()) {
            shared_action->setProperty("dhp", proto_action.properties().dhp().value());
        }
        if (proto_action.properties().has_duration()) {
            shared_action->setProperty("duration", proto_action.properties().duration().value());
        }
        if (proto_action.properties().has_every_turn()) {
            shared_action->setProperty("every_turn", proto_action.properties().every_turn().value());
        }
        state.getActionObserver().addAction(shared_action);
    }
    return state;
}
