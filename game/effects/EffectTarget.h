//
// Created by Vincent Neel on 24/10/2023.
//

#ifndef LIFE_EFFECTTARGET_H
#define LIFE_EFFECTTARGET_H

#include <string>

enum EffectTargetScope {
    Building,
    Resource,
};

struct EffectTarget {
    EffectTarget(EffectTargetScope scope, std::string target) : scope(scope), target(std::move(target)) {}

    EffectTargetScope const scope;
    std::string const target;
};


#endif//LIFE_EFFECTTARGET_H
