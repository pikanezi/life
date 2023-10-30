//
// Created by Vincent Neel on 27/10/2023.
//

#include "Cost.h"

class Cost Cost::from_json(Json::Value const &value) {
    auto increase_ratio = value["price_ratio"].asDouble();
    auto cost = Cost(increase_ratio);
    cost.amount = value["amount"].asDouble();
    cost.resource_id = value["resource"].asString();

    return cost;
}