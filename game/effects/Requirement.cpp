//
// Created by Vincent Neel on 24/10/2023.
//

#include "Requirement.h"
#include "../GameManager.h"
#include "Effect.h"

bool Requirement::satisfied(GameManager const &manager) const {
    switch (possibility) {
        case None:
            return true;
        case Unlocked:
            return manager.is_target_unlocked(target);
    }
    return false;
}

class Requirement Requirement::from_json(Json::Value const &value, Effect const &owning_effect) {
    // if no target specified, we inherit it from the effect
    auto const target = value["target"] ? EffectTarget(
                                                  EffectMappers::targets[value["target"][0].asString()], value["target"][1].asString())
                                        : owning_effect.target;
    auto const possibility = possibilities[value["toBe"].asString()];

    return {.target = target, .possibility = possibility};
}
