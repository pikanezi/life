//
// Created by Vincent Neel on 27/10/2023.
//

#ifndef LIFE_COST_H
#define LIFE_COST_H


#include <string>
#include <json/value.h>

class Cost {
public:
    explicit Cost(double increase_ratio) : increase_ratio(increase_ratio) {}

    static class Cost from_json(const Json::Value &value);

public:
    std::string resource_id;
    double amount;
    const double increase_ratio;
};


#endif //LIFE_COST_H
