//
// Created by Vincent Neel on 18/10/2023.
//

#include <algorithm>

#include "../GameManager.h"
#include "Effect.h"
#include "Requirement.h"

bool Effect::can_activate(GameManager const &manager) const {
    return all_of(requirements.cbegin(), requirements.cend(),
                  [&](Requirement const &requirement) { return requirement.satisfied(manager); });
}

class Effect Effect::from_json(Json::Value const &value) {
    auto kind = EffectMappers::kinds[value["kind"].asString()];
    auto operation = EffectMappers::operations[value["operation"].asString()];
    auto magnitude = value["magnitude"].asDouble();
    auto target_scope = EffectMappers::targets[value["target"][0].asString()];
    auto target_detail = value["target"][1].asString();
    auto sender_scope = EffectMappers::targets[value["sender"][0].asString()];
    auto sender_detail = value["sender"][1].asString();
    auto duration = value["duration"] ? EffectMappers::durations[value["duration"].asString()] : Instant;
    auto interval = value["durationInterval"].asDouble();

    auto effect = Effect(kind, operation, EffectTarget(sender_scope, sender_detail), EffectTarget(target_scope, target_detail), duration, magnitude);
    effect.interval = interval;
    if (auto const &requirements = value["requires"]) {
        for (auto const &requirement: requirements) {
            effect.requirements.push_back(Requirement::from_json(requirement, effect));
        }
    }

    return effect;
}

Effect Effect::from_effect(Effect const &effect, EffectTarget const &sender) {
    auto new_effect = Effect(effect.kind, effect.operation, sender, effect.target, effect.duration, effect.magnitude);
    new_effect.interval = effect.interval;

    return new_effect;
}