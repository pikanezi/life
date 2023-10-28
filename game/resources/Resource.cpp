//
// Created by Vincent Neel on 16/10/2023.
//

#include "Resource.h"

class Resource Resource::from_json(const Json::Value &value) {
    auto unlocked = value["unlocked"] && value["unlocked"].asBool();
    auto resource = Resource(value["id"].asString(), unlocked);

    return resource;
}
