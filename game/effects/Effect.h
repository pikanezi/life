//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_EFFECT_H
#define LIFE_EFFECT_H

#include <map>
#include <tuple>
#include <string>
#include <json/value.h>

enum EffectKind {
    Price,
    Production,
    Consumption,
};

enum EffectOperation {
    Additive,
    Multiplicative,
};

enum EffectTarget {
    Building,
    Resource,
};

template<typename T>
using map_of = std::map<std::string, T>;

class Effect {
public:
    explicit Effect(EffectKind kind, EffectOperation operation, std::tuple<EffectTarget, std::string> target,
                    float magnitude) : kind(kind),
                                       target(std::move(target)),
                                       operation(operation),
                                       magnitude(magnitude) {}

    static class Effect from_json(const Json::Value &value);

public:
    const EffectKind kind;
    const EffectOperation operation;
    const std::tuple<EffectTarget, std::string> target;
    float magnitude;

private:
    inline static map_of<EffectKind> kinds = {
            {"price",       Price},
            {"production",  Production},
            {"consumption", Consumption}
    };

    inline static map_of<EffectOperation> operations = {
            {"additive", Additive},
            {"multiplicative", Multiplicative},
    };

    inline static map_of<EffectTarget> targets = {
            {"building", Building},
            {"resource", Resource},
    };
};


#endif //LIFE_EFFECT_H
