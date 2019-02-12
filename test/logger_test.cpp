// Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

// SYSTEM INCLUDES
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <spdlog/spdlog.h>

// PROJECT INCLUDES
#include "logger.hpp"
#include "utility/shared_ptr.hpp"
#include "boltalog/defines.hpp"

namespace btr
{

namespace log
{

//--------------------------------------------------------------------------------------------------

class LoggerTest : public testing::Test
{
public:

// LIFECYCLE

  LoggerTest(const std::string& fname = "test.log") :
    fname_(fname),
    spd_logger_(spdlog::basic_logger_st("mylogger", fname_, true))
  {
    spd_logger_->set_pattern("%Y-%m-%dT%T.%f%z %L [%t]: %v");
    spd_logger_->set_level(spdlog::level::trace);
    test::log::Logger::setBackend(spd_logger_);
  }

  ~LoggerTest()
  {
    spdlog::drop_all();
    //remove(fname_.c_str());
  }

  std::string fname_;
  std::shared_ptr<spdlog::logger> spd_logger_;
};

//--------------------------------------------------------------------------------------------------

std::vector<std::string> readLastLines(
    uint8_t& start_idx, uint8_t count, const std::string& fname = "test.log")
{
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

//---------------------------------------------------------------------------------------------------

TEST_F(LoggerTest, Level)
{
  test::log::Logger* logger = test::log::Logger::instance();

  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(true, logger->filter(i));
  }

  logger->level(0, btr::log::WARN);
  ASSERT_EQ(true, logger->filter(0));
  ASSERT_EQ(false, logger->filter(1));
  ASSERT_EQ(true, logger->filter(2));
  ASSERT_EQ(false, logger->filter(3));
  ASSERT_EQ(false, logger->filter(4));

  logger->level(1, btr::log::ERROR);
  logger->level(3, btr::log::WARN);

  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(true, logger->filter(i));
  }

  ASSERT_EQ(-1, logger->level(5, btr::log::INFO));
}

TEST_F(LoggerTest, Output)
{
  test::log::Logger* logger = test::log::Logger::instance();
  logger->level(0, btr::log::TRACE);

  event1(32, 8);
  event2(65535, 3.03);
  event3(64, 32323, "string", strlen("string"), 4, "string", strlen("string"));
  event4(8, 64, 16, 32, 32, 16, 64, 8, 8.8, "text", 4, "text", 2, "text", 3);
  spd_logger_->flush();

  std::vector<std::string> expected;
  expected.push_back("1,32,8");
  expected.push_back("2,65535,3.030000");
  expected.push_back("3,64,32323,string,4,73:74:72:69:6E:67");
  expected.push_back("4,8,64,16,32,32,16,64,8,8.800000,text,74:65,74:65:78");

  uint8_t start_idx = 0;
  uint8_t count = 4;
  auto lines = readLastLines(start_idx, count);

  for (uint8_t i = 0; i < count; i++, start_idx++) {
    std::cout << lines[start_idx % count] << std::endl;
    std::size_t found = lines[start_idx % count].find(expected[i]);
    ASSERT_NE(std::string::npos, found) << "Actual: " << lines[start_idx % count]
      << ". Expected: " << expected[i];
  }
}

} // namespace log

} // namespace btr
