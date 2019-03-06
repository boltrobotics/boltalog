// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

/** @file */

#ifndef _btr_log_Defines_hpp_
#define _btr_log_Defines_hpp_

// SYSTEM INCLUDES
#include <inttypes.h>
#include <errno.h>

namespace btr
{

namespace log
{

enum LOG_LEVEL {
  TRACE     = 0,
  DEBUG     = 1,
  INFO      = 2,
  WARN      = 3,
  ERROR     = 4,
  CRITICAL  = 5,
  LOGS_OFF  = 6
};

#ifndef MAX_LOG_SIZE 
#define MAX_LOG_SIZE 128
#endif
#ifndef MAX_STRING_SIZE 
#define MAX_STRING_SIZE 96
#endif
#ifndef MAX_HEX_SIZE 
#define MAX_HEX_SIZE 96
#endif
#ifndef BTR_LOG_LEVEL
#define BTR_LOG_LEVEL btr::log::TRACE
#endif
#define LOG_ENOBASE   23000
#define EBADLOGLEVEL  (LOG_ENOBASE + 1)

#if !defined(BTR_LOG_PORT_USB) && !defined(BTR_LOG_PORT_USART)
#define BTR_LOG_PORT_USB 1
#endif

} // namespace log

} // namespace btr

#endif // _btr_log_Defines_hpp_
