// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL v3

#ifndef _btr_log_Defines_hpp_
#define _btr_log_Defines_hpp_

// SYSTEM INCLUDES
#include <cinttypes>
#include <cerrno>

namespace btr
{

namespace log
{

#define MAX_LOG_SIZE 128

enum LOG_LEVEL {
  TRACE     = 0,
  DEBUG     = 1,
  INFO      = 2,
  WARN      = 3,
  ERROR     = 4,
  CRITICAL  = 5,
  LOGS_OFF  = 6
};

} // namespace log

} // namespace btr

#endif // _btr_log_Defines_hpp_
