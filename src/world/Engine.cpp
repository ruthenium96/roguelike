#include "Engine.h"
#include "generator/OnTheFly.h"
#include "state/action/concrete/PlayerDrop.h"
#include "state/action/concrete/PlayerInteract.h"
#include "state/action/concrete/PlayerMove.h"
#include <algorithm>
#include <stdexcept>

namespace world {

Engine::Engine() {
    generator_ = std::make_unique<generator::OnTheFly>();
    // Here I create initial place:
    generateWorldAroundPlayer({0, 0});
}

void Engine::applyCommand(const common::ControllerCommand& command) {
    using common::ControllerCommand;

    auto externalAction = generateExternalAction(command);
    if (externalAction == nullptr) {
        return;
    }

    bool isExternalActionApplied = state_.applyAction(externalAction);
    if (isExternalActionApplied) {
        state_.applyEveryTurnInternalActions();
    } else {
        // TODO: return description string if an external action has false precondition
    }

    generateWorldAroundPlayer(state_.getObjectObserver().getPlayer()->getCoordinate());
}

common::WorldUITransfer Engine::getWorldUITransfer() const {
    common::WorldUITransfer worldUiTransfer;

    {
        common::Map map;
        auto playerCoordinate = state_.getObjectObserver().getPlayer()->getCoordinate();
        int32_t VISIBILITY = 10;
        for (int32_t dx = -VISIBILITY; dx <= VISIBILITY; ++dx) {
            for (int32_t dy = -VISIBILITY; dy <= VISIBILITY; ++dy) {
                common::Coordinate currentCoordinate = {playerCoordinate.x + dx, playerCoordinate.y + dy};
                auto objects = state_.getObjectObserver().getObjectsAtCoordinate(currentCoordinate);
                std::vector<common::ObjectType> objectsTypes(objects.size());
                std::transform(objects.cbegin(), objects.cend(), objectsTypes.begin(), [](const auto& object) {
                    return object->getObjectType();
                });
                map[currentCoordinate] = objectsTypes;
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
        worldUiTransfer.playerMetrics = playerMetrics;
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

std::shared_ptr<state::action::AbstractAction>
Engine::generateExternalAction(const common::ControllerCommand& command) const {
    std::shared_ptr<state::action::AbstractAction> externalAction = nullptr;
    // TODO: refactor it

    if (std::holds_alternative<common::NonparameterizedVariant>(command)) {
        auto variant = std::get<common::NonparameterizedVariant>(command);
        switch (variant) {
            case common::NonparameterizedVariant::INTERACT: {
                externalAction = std::make_shared<state::action::PlayerInteract>();
                break;
            }
                // TODO: implement something
            case common::NonparameterizedVariant::IGNORE:
            case common::NonparameterizedVariant::UNKNOWN:
            case common::NonparameterizedVariant::UI_ACTIVATE_INVENTORY:
            case common::NonparameterizedVariant::UI_INVENTORY_APPLY:
            case common::NonparameterizedVariant::UI_INVENTORY_DROP:
            case common::NonparameterizedVariant::EXIT: {
                break;
            }
        }
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
                // throw is better than ignore
                throw std::runtime_error("unknown command sent to engine");
        }
        externalAction = std::make_shared<state::action::PlayerMove>(delta_x, delta_y);
    } else if (std::holds_alternative<common::UiMoveInventory>(command)) {
        // TODO: do nothing
    } else if (std::holds_alternative<common::ApplyItem>(command)) {
        auto variant = std::get<common::ApplyItem>(command);
        // TODO: Implement activation
    } else if (std::holds_alternative<common::DropItem>(command)) {
        auto variant = std::get<common::DropItem>(command);
        externalAction = std::make_shared<state::action::PlayerDrop>(variant.type);
    } else {
        // throw is better than ignore
        throw std::runtime_error("unknown command sent to engine");
    }

    return externalAction;
}

}  // namespace world