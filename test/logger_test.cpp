/* Copyright (C) 2017 Bolt Robotics <info@boltrobotics.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */

// SYSTEM INCLUDES
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

// PROJECT INCLUDES
#include "logger.hpp"

namespace slog {

std::vector<std::string> readLastLines(
        uint8_t& start_idx,
        uint8_t count,
        const std::string& fname = "/var/log/user.log") {

    start_idx = 0;
    std::ifstream f(fname);
    std::vector<std::string> lines(count, "");

    if (f.is_open()) {
        std::string line;

        while (std::getline(f, line)) {
            lines[start_idx % count] = line;
            ++start_idx;
        }
    }
    return lines;
}

TEST(LoggerTest, instance) {
    Logger* logger = Logger::init("logger_test");
    EXPECT_EQ(logger, Logger::instance());
}

TEST(LoggerTest, Level) {
    Logger* logger = Logger::init("logger_test");

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(logger->filter(i), true);
    }

    logger->level(0, LOG_WARNING);
    EXPECT_EQ(logger->filter(0), true);
    EXPECT_EQ(logger->filter(1), false);
    EXPECT_EQ(logger->filter(2), true);
    EXPECT_EQ(logger->filter(3), false);

    logger->level(1, LOG_ERR);
    logger->level(3, LOG_WARNING);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(logger->filter(i), true);
    }

    EXPECT_EQ(-1, logger->level(4, LOG_INFO));
}

TEST(DISABLED_LoggerTest, Output) {
    // The test is disabled because it refers to example log events, and when it is
    // built as part of other project, the referred-to events are not defined. This
    // would cause compilation problems.

#if 0

    // Make sure rsyslog is configured to output LOG_USER logs to /var/log/user.log
    // and the file is readable.
    Logger::init("logger_test");
    onLogEventA(32, 8);
    onLogEventB(16, "param2");
    onLogEventC(64, "p2", "p3", 4);

    std::vector<std::string> expected;
    expected.push_back("1,32,8");
    expected.push_back("2,16,param2");
    expected.push_back("3,64,p2,p3,4");

    uint8_t start_idx = 0;
    uint8_t count = 3;
    auto lines = readLastLines(start_idx, count);

    for (uint8_t i = 0; i < count; i++, start_idx++) {
        std::size_t found = lines[start_idx % count].find(expected[i]);
        EXPECT_NE(std::string::npos, found) << "Not found: " << expected[i];
    }
#endif
}

} // namespace slog
