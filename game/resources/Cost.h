//
// Created by Vincent Neel on 27/10/2023.
//

#ifndef LIFE_COST_H
#define LIFE_COST_H


#include <json/value.h>
#include <string>

class Cost {
public:
    explicit Cost(double increase_ratio) : increase_ratio(increase_ratio) {}

    static class Cost from_json(Json::Value const &value);

public:
    std::string resource_id;
    double amount;
    double const increase_ratio;
};


#endif//LIFE_COST_H
