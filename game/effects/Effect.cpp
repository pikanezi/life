//
// Created by Vincent Neel on 18/10/2023.
//

#include <algorithm>

#include "Effect.h"
#include "Requirement.h"
#include "../GameManager.h"

bool Effect::can_activate(const GameManager &manager) const {
    return all_of(requirements.cbegin(), requirements.cend(),
                  [&](const Requirement &requirement) { return requirement.satisfied(manager); });
}

class Effect Effect::from_json(const Json::Value &value) {
    auto kind = EffectMappers::kinds[value["kind"].asString()];
    auto operation = EffectMappers::operations[value["operation"].asString()];
    auto magnitude = value["magnitude"].asDouble();
    auto target = value["target"][0].asString();
    auto target_scope = EffectMappers::targets[value["target"][0].asString()];
    auto target_detail = value["target"][1].asString();
    auto duration = value["duration"] ? EffectMappers::durations[value["duration"].asString()] : Instant;
    auto interval = value["durationInterval"].asDouble();

    auto effect = Effect(kind, operation, EffectTarget(target_scope, target), duration, magnitude);
    effect.interval = interval;
    if (const auto &requirements = value["requires"]) {
        for (const auto &requirement: requirements) {
            effect.requirements.push_back(Requirement::from_json(requirement, effect));
        }
    }

    return effect;
}