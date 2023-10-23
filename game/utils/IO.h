//
// Created by Vincent Neel on 20/10/2023.
//

#ifndef LIFE_IO_H
#define LIFE_IO_H

#include <string>

class IO {
public:
    static std::string read_file(const std::string_view& path);
};


#endif //LIFE_IO_H
