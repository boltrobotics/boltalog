// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

#ifndef _btr_log_Defines_hpp_
#define _btr_log_Defines_hpp_

// SYSTEM INCLUDES
#include <inttypes.h>
#include <errno.h>

namespace btr
{

namespace log
{

#ifndef MAX_LOG_SIZE 
#define MAX_LOG_SIZE 128
#endif
#ifndef MAX_STRING_SIZE 
#define MAX_STRING_SIZE 96
#endif
#ifndef MAX_HEX_SIZE 
#define MAX_HEX_SIZE 96
#endif

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
