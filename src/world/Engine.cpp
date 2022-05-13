#include "Engine.h"
#include "generator/OnTheFly.h"
#include "state/action/external/PlayerDrop.h"
#include "state/action/external/PlayerWorldInteract.h"
#include "state/action/internal/Move.h"
#include "state/action/external/PlayerUIInteract.h"
#include <algorithm>
#include <valarray>

namespace world {

Engine::Engine() {
    initialize();
}

common::Command Engine::applyCommand(const common::Command& command)  {
    using common::Command;

    auto mbExternalAction = generateExternalAction(command);
    if (mbExternalAction.has_value()) {
        auto externalAction = mbExternalAction.value();

        bool isExternalActionApplied = state_.applyAction(externalAction);
        if (isExternalActionApplied) {
            state_.applyEveryTurnInternalActions();
        } else {
            generateErrorMessageForUI(command);
        }

        generateWorldAroundPlayer(state_.getObjectObserver().getPlayer()->getCoordinate());
    }
    if (checkIfPlayerIsAlive()) {
        return getWorldUITransfer();
    } else {
        return common::Death();
    }
}

common::WorldUITransfer Engine::getWorldUITransfer() const {
    common::WorldUITransfer worldUiTransfer;

    {
        common::Map map;
        auto playerCoordinate = state_.getObjectObserver().getPlayer()->getCoordinate();
        auto vision = std::any_cast<int32_t>(state_.getObjectObserver().getPlayer()->getProperty("vision").value());
        for (int32_t dx = -vision; dx <= vision; ++dx) {
            int32_t sqrt = std::sqrt(vision * vision - dx * dx);
            for (int32_t dy = -sqrt; dy <= sqrt; ++dy) {
                common::Coordinate relativeCoordinate = {dx, dy};
                common::Coordinate absoluteCoordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
                auto objects = state_.getObjectObserver().getObjectsAtCoordinate(absoluteCoordinate);
                std::vector<common::ObjectType> objectsTypes(objects.size());
                std::transform(objects.cbegin(), objects.cend(), objectsTypes.begin(), [](const auto& object) {
                    return object->getObjectType();
                });
                map[relativeCoordinate] = objectsTypes;
            }
        }
        worldUiTransfer.map = map;
    }
    {
        common::Inventory inventory;
        for (const auto& item : state_.getObjectObserver().getPlayer()->getItems()) {
            common::ItemData itemData;
            itemData.itemType = item->getItemType();
            // TODO: where should we keep description?
            itemData.description = "";
            inventory.push_back(itemData);
        }
        worldUiTransfer.inventory = inventory;
    }
    {
        common::PlayerMetrics playerMetrics;
        auto player = state_.getObjectObserver().getPlayer();
        playerMetrics.hp = std::any_cast<int32_t>(player->getProperty("hp").value());
        playerMetrics.lvl = std::any_cast<int32_t>(player->getProperty("lvl").value());
        playerMetrics.xp = std::any_cast<int32_t>(player->getProperty("xp").value());
        playerMetrics.attack = std::any_cast<int32_t>(player->getProperty("attack").value());
        playerMetrics.defence = std::any_cast<int32_t>(player->getProperty("defence").value());
        worldUiTransfer.playerMetrics = playerMetrics;
    }
    {
        common::PlayerEquipment playerEquipment;
        auto player = state_.getObjectObserver().getPlayer();
        if (player->getProperty("armor").has_value()) {
            auto armorItemType = std::any_cast<common::ItemType>(player->getProperty("armor").value());
            playerEquipment.armor = armorItemType;
        }
        if (player->getProperty("leftHand").has_value()) {
            auto leftHandItemType = std::any_cast<common::ItemType>(player->getProperty("leftHand").value());
            playerEquipment.leftHand = leftHandItemType;
        }
        if (player->getProperty("rightHand").has_value()) {
            auto rightHandItemType = std::any_cast<common::ItemType>(player->getProperty("rightHand").value());
            playerEquipment.rightHand = rightHandItemType;
        }
        worldUiTransfer.playerEquipment = playerEquipment;
    }
    {
        worldUiTransfer.message = errorMessageForUi;
        errorMessageForUi = std::nullopt;
    }
    return worldUiTransfer;
}

void Engine::generateWorldAroundPlayer(common::Coordinate playerCoordinate) {
    int32_t GENSIZE = 10;
    for (int32_t dx = -GENSIZE; dx <= GENSIZE; ++dx) {
        for (int32_t dy = -GENSIZE; dy <= GENSIZE; ++dy) {
            common::Coordinate coordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
            auto objectsAndActions = generator_->generateObjects(coordinate, state_.getObjectObserver());
            for (const auto& objectAndActions : objectsAndActions) {
                state_.getObjectObserver().addObject(objectAndActions.object);
                for (const auto& action : objectAndActions.actions) {
                    state_.addAction(action);
                }
            }
        }
    }
}

std::optional<std::shared_ptr<state::action::AbstractAction>>
Engine::generateExternalAction(const common::Command& command) const {
    std::optional<std::shared_ptr<state::action::AbstractAction>> externalAction = std::nullopt;
    // TODO: refactor it

    if (std::holds_alternative<common::Ignore>(command)) {
        // do nothing
    } else if (std::holds_alternative<common::Interact>(command)) {
        externalAction = std::make_shared<state::action::PlayerWorldInteract>();
    } else if (std::holds_alternative<common::Move>(command)) {
        auto variant = std::get<common::Move>(command);
        int32_t delta_x;
        int32_t delta_y;
        switch (variant.direction) {
            case common::Direction::TOP:
                delta_x = 0;
                delta_y = -1;
                break;
            case common::Direction::LEFT:
                delta_x = -1;
                delta_y = 0;
                break;
            case common::Direction::BOTTOM:
                delta_x = 0;
                delta_y = 1;
                break;
            case common::Direction::RIGHT:
                delta_x = 1;
                delta_y = 0;
                break;
            default:
                assert(0);
        }
        auto playerIdentity = state_.getObjectObserver().getPlayer()->getIdentity();
        externalAction = std::make_shared<state::action::Move>(playerIdentity, delta_x, delta_y);
    } else if (std::holds_alternative<common::World_ApplyItem>(command)) {
        auto variant = std::get<common::World_ApplyItem>(command);
        externalAction = std::make_shared<state::action::PlayerUIInteract>(variant.type, variant.equipmentPosition);
    } else if (std::holds_alternative<common::World_DropItem>(command)) {
        auto variant = std::get<common::World_DropItem>(command);
        externalAction = std::make_shared<state::action::PlayerDrop>(variant.type);
    } else {
        // Unknown, Exit, UIInventoryDrop, UIInventoryApply, ChangeRegime, UiMoveInventory
        assert(0);
    }

    return externalAction;
}

void Engine::generateErrorMessageForUI(const common::Command& command) {
    if (std::holds_alternative<common::Ignore>(command)) {
        return;
    } else if (std::holds_alternative<common::Interact>(command)) {
        errorMessageForUi = "Nothing to interact!";
    } else if (std::holds_alternative<common::Move>(command)) {
        errorMessageForUi = "Cannot move here!";
    } else if (std::holds_alternative<common::World_ApplyItem>(command)) {
        errorMessageForUi = "Need more items!";
    } else if (std::holds_alternative<common::World_DropItem>(command)) {
        errorMessageForUi = "Cannot drop!";
    } else {
        // Unknown, Exit, UIInventoryDrop, UIInventoryApply, ChangeRegime, UiMoveInventory
        assert(0);
    }
}

bool Engine::checkIfPlayerIsAlive() const {
    auto playerHP = std::any_cast<int32_t>(state_.getObjectObserver().getPlayer()->getProperty("hp").value());
    return playerHP > 0;
}

void Engine::initialize() {
    generator_ = std::make_unique<generator::OnTheFly>();
    // Here I create initial place:
    generateWorldAroundPlayer({0, 0});
}

void Engine::resetWorld() {
    state_ = state::State();
    errorMessageForUi = std::nullopt;
    initialize();
}

}  // namespace world