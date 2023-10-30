//
// Created by Vincent Neel on 28/10/2023.
//

#include <chrono>
#include <fmt/core.h>
#include <iostream>

#include "Logger.h"

void Logger::log(std::string const &message) const {
    if (!enabled) {
        return;
    }
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                          now.time_since_epoch())
                          .count() %
                  1000;
    auto time = std::chrono::system_clock::to_time_t(now);
    char timeString[std::size("yyyy-mm-dd hh:mm:ss")];
    std::strftime(std::data(timeString), std::size(timeString),
                  "%F %T", std::gmtime(&time));
    std::cout << fmt::format("{}{}:{}{}: {}\n", BOLDYELLOW, timeString, millis, RESET, message);
}