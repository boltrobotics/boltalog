/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// SYSTEM INCLUDES
#include <gtest/gtest.h>
#include <iostream>

// PROJECT INCLUDES
#include "logger.hpp"

namespace slog {

TEST(TestCase, TestName)
{
    Logger::make("", LOG_LOCAL2, LOG_DEBUG);
    onLogEventA(32, 8);
    onLogEventB(16, "param2");
    onLogEventC(64, "p2", "p3", 4);
}

TEST(TestCase, TestName2)
{
    EXPECT_EQ(1, 0);
}

TEST(TestCase, TestName3)
{
    EXPECT_EQ(1, 1);
}

} // namespace slog
