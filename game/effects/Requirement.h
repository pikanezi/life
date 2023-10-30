//
// Created by Vincent Neel on 24/10/2023.
//

#ifndef LIFE_REQUIREMENT_H
#define LIFE_REQUIREMENT_H

#include <json/value.h>

#include "EffectTarget.h"

class GameManager;

enum RequirementPossibility {
    None,
    Unlocked
};

class Requirement {
public:
    bool satisfied(GameManager const &manager) const;

    static class Requirement from_json(Json::Value const &value, class Effect const &owning_effect);

public:
    EffectTarget target;
    RequirementPossibility possibility = None;

private:
    inline static std::map<std::string, RequirementPossibility> possibilities = {
            {"none", None},
            {"unlocked", Unlocked}};
};


#endif//LIFE_REQUIREMENT_H
