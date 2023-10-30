//
// Created by Vincent Neel on 18/10/2023.
//

#ifndef LIFE_EFFECT_H
#define LIFE_EFFECT_H

#include <json/value.h>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "EffectTarget.h"
#include "Requirement.h"

enum EffectKind {
    Price,
    Unlock,
    Production,
    Consumption,
};

enum EffectDuration {
    Instant,
    Interval,
    Continuous,
};

enum EffectOperation {
    Additive,
    Multiplicative,
};

template<typename T>
using map_of = std::map<std::string, T>;

class GameManager;

class Effect {
public:
    explicit Effect(EffectKind kind,
                    EffectOperation operation,
                    EffectTarget target,
                    EffectDuration duration,
                    double magnitude) : kind(kind),
                                        target(std::move(target)),
                                        operation(operation),
                                        duration(duration),
                                        magnitude(magnitude) {}

    bool can_activate(GameManager const &manager) const;

    static class Effect from_json(Json::Value const &value);

public:
    EffectKind const kind;
    EffectDuration const duration;
    EffectOperation const operation;
    EffectTarget const target;

    double magnitude;
    double interval;

    std::vector<class Requirement> requirements;
};

struct EffectMappers {
    inline static map_of<EffectKind> kinds = {
            {"price",       Price      },
            {"production",  Production },
            {"consumption", Consumption}
    };

    inline static map_of<EffectDuration> durations = {
            {"instant",    Instant   },
            {"continuous", Continuous},
            {"interval",   Interval  },
    };

    inline static map_of<EffectOperation> operations = {
            {"additive",       Additive      },
            {"multiplicative", Multiplicative},
    };

    inline static map_of<EffectTargetScope> targets = {
            {"building", Building},
            {"resource", Resource},
    };
};


#endif//LIFE_EFFECT_H
