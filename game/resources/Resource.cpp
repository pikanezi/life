//
// Created by Vincent Neel on 16/10/2023.
//

#include <algorithm>
#include <memory>

#include "Resource.h"

class Resource Resource::from_json(Json::Value const &value) {
    auto unlocked = value["unlocked"] && value["unlocked"].asBool();
    auto resource = Resource(value["id"].asString(), unlocked);

    return resource;
}

void Resource::operator+=(double rhs) {
    if (limit == 0) {
        amount += rhs;
    } else {
        amount = std::clamp(amount + rhs, 0., limit);
    }
}

void Resource::operator*=(double rhs) {
    if (limit == 0) {
        amount += rhs;
    } else {
        amount = std::clamp(amount * rhs, 0., limit);
    }
}
