// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

/** @file */

#ifndef _btr_log_Defines_hpp_
#define _btr_log_Defines_hpp_

// SYSTEM INCLUDES
#define _STDC_FORMAT_MACROS
#include <inttypes.h>

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

#ifndef BTR_LOG_ENABLED
#define BTR_LOG_ENABLED   1
#endif
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

//--------------------------------------------------------------------------------------------------
// Errors

#define BTR_LOG_EINVAL        0
#define BTR_LOG_EBADLOGLEVEL  1
#define BTR_LOG_ERANGE        2
#define BTR_LOG_EIO           3
#define BTR_LOG_ESEND         4
#define BTR_LOG_ECOUNT        (BTR_LOG_ESEND + 1)

#ifndef BTR_LOG_ERR_OFFSET 
#define BTR_LOG_ERR_OFFSET    0
#endif
#ifndef BTR_LOG_ERR_ENABLED
#define BTR_LOG_ERR_ENABLED   BTR_LOG_ECOUNT
#endif

/** Calculate how many byte are required to hold "m" bits. */
#define BTR_ERR_BITS(m) ((m % 8) != 0 ? (m / 8 + 1) : (m / 8))

//--------------------------------------------------------------------------------------------------

} // namespace log

} // namespace btr

#endif // _btr_log_Defines_hpp_
