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

#include <gtest/gtest.h>
#include <syslog.h>
#include <iostream>

int log_level_ = LOG_WARNING;

void log(const std::string&) {
    if (LOG_INFO <= log_level_) {
        std::cout << "Event is output" << std::endl;
    }
}

std::string getStuffSlowly() {
    std::string blah = "hmmm... blah blah";

    for (int i = 0; i < 27; i++) {
        blah += blah;
    }
    return blah;
}

TEST(Doc, BadLogCall) {
    log(getStuffSlowly());
}

TEST(Doc, GoodLogCall) {
    if (LOG_INFO <= log_level_) {
        log(getStuffSlowly());
    }
}

#define onLogEvent(slow_stuff) \
    if (LOG_INFO <= log_level_) { \
        log(slow_stuff); \
    }

TEST(Doc, GoodLogCallMacro) {
    onLogEvent(getStuffSlowly());
}
