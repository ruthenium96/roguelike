#include "ProtobufEngine.h"
#include "../../state/action/internal/Confuse.h"
#include "../../state/action/internal/PickDropItem.h"
#include "../../state/action/internal/Poison.h"
#include "../../state/action/mold/MoldEveryTurn.h"
#include "../../state/action/mold/MoldInteraction.h"
#include "../../state/action/npc/AggressiveNPC.h"
#include "../../state/action/npc/CowardNPC.h"
#include "../../state/action/npc/InactiveNPC.h"
#include "../../state/item/concrete/Ring.h"
#include "../../state/item/concrete/Stick.h"
#include "../../state/object/concrete/Artefact.h"
#include "../../state/object/concrete/Floor.h"
#include "../../state/object/concrete/Mold.h"
#include "../../state/object/concrete/NPC.h"
#include "../../state/object/concrete/Wall.h"
#include <memory>

namespace world::generator::serialization {
void ProtobufEngine::associate_item_types() {
    item_mapper_.associate_types(ProtoSerializer::Item::STICK, common::ItemType::STICK);
    item_mapper_.associate_types(ProtoSerializer::Item::RING, common::ItemType::RING);
}

void ProtobufEngine::associate_action_types() {
    action_mapper_.associate_types(ProtoSerializer::Action::PICK_ITEM, world::state::action::ActionType::PICK_ITEM);
    action_mapper_.associate_types(ProtoSerializer::Action::POISON, world::state::action::ActionType::POISON);
    action_mapper_.associate_types(ProtoSerializer::Action::AGGRESSIVE_NPC,
                                   world::state::action::ActionType::AGRESSIVE_NPC);
    action_mapper_.associate_types(ProtoSerializer::Action::COWARD_NPC, world::state::action::ActionType::COWARD_NPC);
    action_mapper_.associate_types(ProtoSerializer::Action::INACTIVE_NPC,
                                   world::state::action::ActionType::INACTIVE_NPC);
    //    action_mapper_.associate_types(ProtoSerializer::Action::CONFUSE, world::state::action::ActionType::CONFUSE);
    action_mapper_.associate_types(ProtoSerializer::Action::MOLD_INTERACTION,
                                   world::state::action::ActionType::MOLD_INTERACTION);
    action_mapper_.associate_types(ProtoSerializer::Action::MOLD_EVERY_TURN,
                                   world::state::action::ActionType::MOLD_EVERY_TURN);

    actionConstructor_[world::state::action::ActionType::PICK_ITEM] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::PickDropItem>(identity);
    };
    actionConstructor_[world::state::action::ActionType::POISON] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::Poison>(identity);
    };
    actionConstructor_[world::state::action::ActionType::AGRESSIVE_NPC] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::AggressiveNPC>(identity);
    };
    actionConstructor_[world::state::action::ActionType::COWARD_NPC] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::CowardNPC>(identity);
    };
    actionConstructor_[world::state::action::ActionType::INACTIVE_NPC] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::InactiveNPC>(identity);
    };
    //    actionConstructor_[world::state::action::ActionType::CONFUSE] = [](world::state::Identity identity){return
    //    std::make_shared<world::state::action::Confuse>(identity);};
    actionConstructor_[world::state::action::ActionType::MOLD_INTERACTION] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::MoldInteraction>(identity);
    };
    actionConstructor_[world::state::action::ActionType::MOLD_EVERY_TURN] = [](world::state::Identity identity) {
        return std::make_shared<world::state::action::MoldEveryTurn>(identity);
    };
}

void ProtobufEngine::associate_object_types() {
    object_mapper_.associate_types(ProtoSerializer::Object::PLAYER, common::ObjectType::PLAYER);
    object_mapper_.associate_types(ProtoSerializer::Object::ARTEFACT, common::ObjectType::ARTEFACT);
    object_mapper_.associate_types(ProtoSerializer::Object::FLOOR, common::ObjectType::FLOOR);
    object_mapper_.associate_types(ProtoSerializer::Object::WALL, common::ObjectType::WALL);
    object_mapper_.associate_types(ProtoSerializer::Object::NPC, common::ObjectType::NPC);
    object_mapper_.associate_types(ProtoSerializer::Object::MOLD, common::ObjectType::MOLD);

    // TODO: implement it as named constructors
    objectConstructor_[common::ObjectType::PLAYER] = [](world::state::Identity identity) {
        return std::make_shared<world::state::object::Player>(identity);
    };
    objectConstructor_[common::ObjectType::ARTEFACT] = [](world::state::Identity identity) {
        return std::make_shared<world::state::object::Artefact>(identity);
    };
    objectConstructor_[common::ObjectType::FLOOR] = [](world::state::Identity identity) {
        return std::make_shared<world::state::object::Floor>(identity);
    };
    objectConstructor_[common::ObjectType::WALL] = [](world::state::Identity identity) {
        return std::make_shared<world::state::object::Wall>(identity);
    };
    objectConstructor_[common::ObjectType::NPC] = [](world::state::Identity identity) {
        return std::make_shared<world::state::object::NPC>(identity);
    };
    objectConstructor_[common::ObjectType::MOLD] = [](world::state::Identity identity) {
        return std::make_shared<world::state::object::Mold>(identity);
    };
}

ProtobufEngine::ProtobufEngine() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    associate_item_types();
    associate_object_types();
    associate_action_types();
}

ProtoSerializer::State ProtobufEngine::serialize(const world::state::State& state) const {
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
        new_proto_object->mutable_coords()->set_x(coords.x);
        new_proto_object->mutable_coords()->set_y(coords.y);
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
            } else if (key == "attack") {
                proto_properties->mutable_attack()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "defence") {
                proto_properties->mutable_defence()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "vision") {
                proto_properties->mutable_vision()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "growingThreshold") {
                proto_properties->mutable_growingthreshold()->set_value(std::any_cast<float>(value));
            } else {
                assert(0);
            }
        }

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
        // type:
        ProtoSerializer::Action::ActionType action_proto_type =
            action_mapper_.get_proto_associated_type_with(action_ptr->getActionType());
        new_proto_action->set_type(action_proto_type);
        // self-Identity:
        if (action_ptr->getSelfIdentity().has_value()) {
            new_proto_action->set_selfidentity(action_ptr->getSelfIdentity().value().asNumber());
        }
        // Object Identity:
        if (action_ptr->getCorrespondingObjectIdentity().has_value()) {
            new_proto_action->mutable_objectidentity()->set_value(
                action_ptr->getCorrespondingObjectIdentity().value().asNumber());
        }
        // Item Identity:
        if (action_ptr->getCorrespondingItemIdentity().has_value()) {
            new_proto_action->mutable_itemidentity()->set_value(
                action_ptr->getCorrespondingItemIdentity().value().asNumber());
        }
        // properties:
        auto* proto_properties = new_proto_action->mutable_properties();
        for (const auto& [key, value] : action_ptr->getAllProperties()) {
            if (key == "dx") {
                proto_properties->mutable_dx()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "dy") {
                proto_properties->mutable_dy()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "dhp") {
                proto_properties->mutable_dhp()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "duration") {
                proto_properties->mutable_duration()->set_value(std::any_cast<int32_t>(value));
            } else if (key == "every_turn") {
                proto_properties->mutable_every_turn()->set_value(std::any_cast<bool>(value));
            } else if (key == "itemToDrop") {
                proto_properties->mutable_item_to_drop()->set_value(std::any_cast<state::Identity>(value).asNumber());
            } else if (key == "interaction") {
                proto_properties->mutable_interaction()->set_value(std::any_cast<bool>(value));
            } else {
                assert(0);
            }
        }
    }
    return proto_state;
}

world::state::State ProtobufEngine::deserialize(const ProtoSerializer::State& proto_state) const {
    world::state::State state;

    // Objects and Items
    int objects_size = proto_state.objects_size();
    for (int object_index = 0; object_index < objects_size; ++object_index) {
        const ProtoSerializer::Object& proto_object = proto_state.objects(object_index);
        common::ObjectType game_object_type = object_mapper_.get_game_associated_type_with(proto_object.type());

        // type and identity
        std::shared_ptr<world::state::object::AbstractObject> shared_object;
        auto objectIdentity = world::state::Identity(proto_object.selfidentity());
        shared_object = objectConstructor_.at(game_object_type)(objectIdentity);
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
        if (proto_object.properties().has_attack()) {
            shared_object->setProperty("attack", proto_object.properties().attack().value());
        }
        if (proto_object.properties().has_defence()) {
            shared_object->setProperty("defence", proto_object.properties().defence().value());
        }
        if (proto_object.properties().has_vision()) {
            shared_object->setProperty("vision", proto_object.properties().vision().value());
        }
        if (proto_object.properties().has_growingthreshold()) {
            shared_object->setProperty("growingThreshold", proto_object.properties().growingthreshold().value());
        }
        // items
        int items_size = proto_object.items_size();
        for (int item_index = 0; item_index < items_size; ++item_index) {
            const ProtoSerializer::Item& item_proto = proto_object.items(item_index);
            common::ItemType game_item_type = item_mapper_.get_game_associated_type_with(item_proto.type());
            auto itemIdentity = world::state::Identity(item_proto.self_id());
            auto ownerIdentity = world::state::Identity(item_proto.owner_id());
            if (game_item_type == common::ItemType::STICK) {
                shared_object->getItems().push_back(
                    std::make_unique<world::state::item::Stick>(itemIdentity, ownerIdentity));
            } else if (game_item_type == common::ItemType::RING) {
                shared_object->getItems().push_back(
                    std::make_unique<world::state::item::Ring>(itemIdentity, ownerIdentity));
            } else {
                assert(0);
            }
        }
        state.getObjectObserver().addObject(shared_object);
    }
    // actions
    int actions_size = proto_state.actions_size();
    for (int action_index = 0; action_index < actions_size; ++action_index) {
        const ProtoSerializer::Action& proto_action = proto_state.actions(action_index);
        auto game_action_type = action_mapper_.get_game_associated_type_with(proto_action.type());
        // type, identity
        std::shared_ptr<world::state::action::AbstractAction> shared_action;
        auto actionIdentity = world::state::Identity(proto_action.selfidentity());
        shared_action = actionConstructor_.at(game_action_type)(actionIdentity);
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
        if (proto_action.properties().has_item_to_drop()) {
            auto identityToDrop = state::Identity(proto_action.properties().item_to_drop().value());
            shared_action->setProperty("itemToDrop", identityToDrop);
        }
        if (proto_action.properties().has_interaction()) {
            shared_action->setProperty("interaction", proto_action.properties().interaction().value());
        }
        state.getActionObserver().addAction(shared_action);
    }
    return state;
}
}  // namespace world::generator::serialization