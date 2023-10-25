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
    EffectTargetScope scope;
    std::string target;
};


#endif //LIFE_EFFECTTARGET_H
