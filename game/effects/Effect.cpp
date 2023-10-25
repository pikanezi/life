//
// Created by Vincent Neel on 18/10/2023.
//

#include "Effect.h"

class Effect Effect::from_json(const Json::Value &value) {
    auto kind = kinds[value["kind"].asString()];
    auto operation = operations[value["operation"].asString()];
    auto magnitude = value["magnitude"].asFloat();
    auto target = value["target"][0].asString();
    auto target_scope = targets[value["target"][0].asString()];
    auto target_detail = value["target"][1].asString();

    return Effect(kind, operation, EffectTarget{.scope =  target_scope, .target=target}, magnitude);
}