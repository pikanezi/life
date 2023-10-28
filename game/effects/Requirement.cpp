//
// Created by Vincent Neel on 24/10/2023.
//

#include "../GameManager.h"
#include "Effect.h"
#include "Requirement.h"

bool Requirement::satisfied(const GameManager &manager) const {
    switch (possibility) {
        case None:
            return true;
        case Unlocked:
            return manager.is_target_unlocked(target);
    }
    return false;
}

class Requirement Requirement::from_json(const Json::Value &value, const class Effect &owning_effect) {
    // if no target specified, we inherit it from the effect
    const auto target = value["target"] ? EffectTarget(
            EffectMappers::targets[value["target"][0].asString()], value["target"][1].asString())
                                        : owning_effect.target;
    const auto possibility = possibilities[value["toBe"].asString()];

    return {.target = target, .possibility = possibility};
}
