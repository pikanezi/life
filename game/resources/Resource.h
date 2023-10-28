//
// Created by Vincent Neel on 16/10/2023.
//

#ifndef LIFE_RESOURCE_H
#define LIFE_RESOURCE_H

#include <string>
#include <json/json.h>

class Resource {
public:
    explicit Resource(std::string id, bool unlocked) : id(std::move(id)), unlocked(unlocked) {}

    Resource(const Resource& resource) : id(resource.id), unlocked(resource.unlocked) {}

    static class Resource from_json(const Json::Value &value);

public:
    const std::string id;

    double amount = 0;
    double limit = 0;

    bool unlocked = false;
};

#endif //LIFE_RESOURCE_H
