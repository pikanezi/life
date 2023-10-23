//
// Created by Vincent Neel on 20/10/2023.
//

#include <fstream>
#include <fmt/core.h>

#include "IO.h"

std::string IO::read_file(const std::string_view& path) {
        constexpr auto read_size = std::size_t(4096);
        auto stream = std::ifstream(path.data());
        stream.exceptions(std::ios_base::badbit);

        if (not stream) {
            throw std::ios_base::failure(fmt::format("file {} does not exists", path));
        }

        auto out = std::string();
        auto buf = std::string(read_size, '\0');
        while (stream.read(& buf[0], read_size)) {
            out.append(buf, 0, stream.gcount());
        }
        out.append(buf, 0, stream.gcount());
        return out;
}
