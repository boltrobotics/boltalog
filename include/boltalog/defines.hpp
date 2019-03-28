// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

/** @file */

#ifndef _boltalog_btr_Defines_hpp_
#define _boltalog_btr_Defines_hpp_

// SYSTEM INCLUDES
#define _STDC_FORMAT_MACROS
#include <inttypes.h>

namespace btr
{

enum BTR_LOG_LEVEL {
  TRACE     = 0,
  DEBUG     = 1,
  INFO      = 2,
  WARN      = 3,
  ERROR     = 4,
  CRITICAL  = 5,
  LOGS_OFF  = 6
};

#ifndef BTR_LOG_ENABLED
#if BTR_X86 > 0
#define BTR_LOG_ENABLED         1
#else
#define BTR_LOG_ENABLED         0
#endif
#endif

/**
 * Set default port for logging output by setting BTR_LOG_PORT_USB or BTR_LOG_PORT_USART to a value
 * between 0 and maximum platform-supported port. If both are defined, USB will be used. */
#if !defined(BTR_LOG_PORT_USB) && !defined(BTR_LOG_PORT_USART)
#define BTR_LOG_PORT_USB        1
#endif

#ifndef BTR_LOG_MAX
#define BTR_LOG_MAX             128
#endif
#ifndef BTR_LOG_MAX_STRING
#define BTR_LOG_MAX_STRING      96
#endif
#ifndef BTR_LOG_MAX_HEX
#define BTR_LOG_MAX_HEX         96
#endif
#ifndef BTR_LOG_LEVEL_DFLT
#define BTR_LOG_LEVEL_DFLT      btr::TRACE
#endif

//==================================================================================================
// Status {

#define BTR_LOG_ENOERR          0x00000000
#define BTR_LOG_EINVAL          0x00010000
#define BTR_LOG_EBADLOGLEVEL    0x00020000
#define BTR_LOG_ERANGE          0x00040000
#define BTR_LOG_EIO             0x00080000
#define BTR_LOG_ESEND           0x00100000

#ifndef BTR_STATUS_ENABLED
#define BTR_STATUS_ENABLED      1
#endif

namespace log
{
/** Provide this module's status accumulator or nullptr if BTR_STATUS_ENABLED is 0. */
uint32_t* status();
}

// } Status

} // namespace btr

#endif // _boltalog_btr_Defines_hpp_
