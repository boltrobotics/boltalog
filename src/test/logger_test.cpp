/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// SYSTEM INCLUDES
#include <gtest/gtest.h>
#include <iostream>

// PROJECT INCLUDES
#include "logger.hpp"

TEST(TestCase, TestName)
{
    EXPECT_EQ(1, 1);
#if 0
    onLogEvent1(32, "param2", "param3");
    onLogEvent2(16, "param2");
    onLogEvent3(64, 8, "param3", "param4");
#endif
}

TEST(TestCase, TestName2)
{
    EXPECT_EQ(1, 0);
}

TEST(TestCase, TestName3)
{
    EXPECT_EQ(1, 1);
}
