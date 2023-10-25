//
// Created by Vincent Neel on 16/10/2023.
//

#ifndef LIFE_RESOURCE_H
#define LIFE_RESOURCE_H

#include <string>

class Resource {
public:
    explicit Resource(std::string id) : id(std::move(id)) {}

public:
    const std::string id;

    double amount = 0;
    double limit = 0;
};

#endif //LIFE_RESOURCE_H
