//
// Created by Vincent Neel on 24/10/2023.
//

#ifndef LIFE_REQUIREMENT_H
#define LIFE_REQUIREMENT_H

#include <json/value.h>

class Requirement {
public:
    static class Requirement from_json(const Json::Value &value, const class Effect &owning_effect);
};


#endif //LIFE_REQUIREMENT_H
