//
// Created by Vincent Neel on 18/10/2023.
//

#include <algorithm>

#include "../GameManager.h"
#include "Building.h"

bool Building::can_afford(GameManager const &manager) const {
    return std::all_of(cost.cbegin(), cost.cend(),
                       [&](Cost const &c) {
                           return manager.resource_by_id(c.resource_id)->amount >= c.amount;
                       });
}

class Building Building::from_json(Json::Value const &value) {
    Building building;
    building.id = value["id"].asString();
    building.unlocked = value["unlocked"] && value["unlocked"].asBool();

    if (value["cost"]) {
        for (auto const &v: value["cost"]) {
            building.cost.push_back(Cost::from_json(v));
        }
    }
    auto const sender = EffectTarget(EffectTargetScope::Building, building.id);
    if (value["buildEffects"]) {
        for (auto const &v: value["buildEffects"]) {
            building.build_effects.push_back(Effect::from_effect(Effect::from_json(v), sender));
        }
    }
    if (value["updateEffects"]) {
        for (auto const &v: value["updateEffects"]) {
            building.update_effects.push_back(Effect::from_effect(Effect::from_json(v), sender));
        }
    }
    return building;
}
