//
// Created by Vincent Neel on 20/10/2023.
//

#include <fmt/core.h>
#include <fstream>
#include <json/json.h>
#include <stdexcept>

#include "IO.h"

std::string IO::read_file(std::string_view const &path) {
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    if (not stream) {
        throw std::ios_base::failure(fmt::format("file {} does not exists", path));
    }

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

Json::Value IO::read_file_as_json(std::string_view const &path) {
    auto file_content = IO::read_file(path);
    Json::CharReaderBuilder builder{};
    auto reader = std::unique_ptr<Json::CharReader>(builder.newCharReader());
    Json::Value root{};
    std::string errors{};
    auto const is_parsed = reader->parse(file_content.c_str(),
                                         file_content.c_str() + file_content.length(),
                                         &root,
                                         &errors);
    if (!is_parsed) {
        throw std::runtime_error(fmt::format("could not parse file {}:", path, errors));
    }

    return root;
}