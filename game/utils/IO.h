//
// Created by Vincent Neel on 20/10/2023.
//

#ifndef LIFE_IO_H
#define LIFE_IO_H

#include <json/value.h>
#include <string>

class IO {
public:
    static std::string read_file(std::string_view const &path);

    static Json::Value read_file_as_json(std::string_view const &path);
};


#endif//LIFE_IO_H
