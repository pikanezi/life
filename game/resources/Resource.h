//
// Created by Vincent Neel on 16/10/2023.
//

#ifndef LIFE_RESOURCE_H
#define LIFE_RESOURCE_H

#include <json/json.h>
#include <string>

class Resource {
public:
    explicit Resource(std::string id, bool unlocked) : id(std::move(id)), unlocked(unlocked) {}

    Resource(Resource const &resource) : id(resource.id), unlocked(resource.unlocked) {}

    static class Resource from_json(Json::Value const &value);

    void operator+=(double rhs);

    void operator*=(double rhs);

public:
    std::string const id;

    double amount = 0;
    double limit = 0;

    bool unlocked = false;
};

#endif//LIFE_RESOURCE_H
