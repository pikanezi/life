//
// Created by Vincent Neel on 18/10/2023.
//

#include <memory>
#include <fmt/core.h>

#include "Game.h"
#include "GameManager.h"
#include "effects/Effect.h"
#include "resources/Resource.h"

void GameManager::update(double delta_time) {
    for (auto &[_, building]: buildings) {
    }
}

void GameManager::construct(const std::string &building_id) {
    const auto &building = buildings[building_id];
    if (!building->can_afford(*this)) {
        game.logger.log(fmt::format("can't afford building {}", building_id));
        return;
    }

    EffectTarget target = EffectTarget(Building, building_id);
    for (const auto &c: building->cost) {
        const auto cost_effect = Effect(Consumption, Additive, target, Instant, -c.amount);
        apply_effect(cost_effect);
    }
    for (const auto &effect: building->build_effects) {
        apply_effect(effect);
    }
    building->amount_owned += 1;
    game.logger.log(fmt::format("building {} constructed", building_id));
}

void GameManager::apply_effect(const Effect &effect) {
    if (!effect.can_activate(*this)) {
        return;
    }
    if (effect.duration != Instant) {
        if (effect.target.scope == Building) {
            buildings[effect.target.target]->active_effects.push_back(effect);
        } else {
            active_effects.push_back(effect);
        }
        return;
    }
    execute_effect(effect);
}

void GameManager::execute_effect(const Effect &effect) {
    switch (effect.kind) {
        case Unlock:
            switch (effect.target.scope) {
                case Building:
                    buildings[effect.target.target]->unlocked = true;
                case Resource:
                    resources[effect.target.target]->unlocked = true;
            }
            break;
        case Price:
        case Production:
        case Consumption:
            switch (effect.target.scope) {
                case Resource:
                    if (effect.operation == Additive) {
                        *resources[effect.target.target] += effect.magnitude;
                    } else {
                        *resources[effect.target.target] *= effect.magnitude;
                    }
                    break;
                case Building:
                    if (effect.operation == Additive) {
                        buildings[effect.target.target]->amount_owned += int(effect.magnitude);
                    } else {
                        buildings[effect.target.target]->amount_owned *= int(effect.magnitude);
                    }
                    break;
            }
            break;
    }
}

const class Resource *GameManager::resource_by_id(const string &resource_id) const {
    return resources.at(resource_id).get();
}

const class Building *GameManager::building_by_id(const std::string &building_id) const {
    return buildings.at(building_id).get();
}

bool GameManager::is_resource_unlocked(const string &resource_id) const {
    return resources.contains(resource_id);
}

bool GameManager::is_building_unlocked(const std::string &building_id) const {
    return buildings.contains(building_id);
}

void GameManager::load_building(unique_ptr<class Building> building) {
    buildings[building->id] = std::move(building);
}

void GameManager::load_resource(unique_ptr<class Resource> resource) {
    resources[resource->id] = std::move(resource);
}

bool GameManager::is_target_unlocked(const EffectTarget &target) const {
    switch (target.scope) {
        case Resource:
            is_resource_unlocked(target.target);
        case Building:
            is_building_unlocked(target.target);
    }
    return false;
}

void GameManager::increment_food() {
    const auto add_food_effect = Effect(Consumption, Additive, EffectTarget(Resource, "food"), Instant, 1.f);
    apply_effect(add_food_effect);
}