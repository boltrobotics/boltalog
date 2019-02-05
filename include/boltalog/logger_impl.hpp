// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

#ifndef _btr_log_LoggerImpl_hpp_
#define _btr_log_LoggerImpl_hpp_

// SYSTEM INCLUDES
#if defined(x86)
#include <memory>
#elif defined(avr)
#include <Stream.h>
#endif

// PROJECT INCLUDES
#include "boltalog/defines.hpp"

namespace spdlog
{

class logger;

}

namespace btr
{

namespace log
{

/**
 *
 */
class LoggerImpl
{
public:

// LIFECYCLE

  /**
   * Use stderr console logger on x86.
   * Use Serial on AVR.
   */
  LoggerImpl();

  /**
   * @param logger - platform-specific instance
   */
#if defined(x86)
  LoggerImpl(std::shared_ptr<spdlog::logger> logger);
#elif defined(avr)
  LoggerImpl(Stream& logger);
#elif defined(stm32)
#endif

// OPERATIONS

#if defined(x86)
  std::shared_ptr<spdlog::logger> backend();
#elif defined(avr)
  Stream& backend();
#elif defined(stm32)
#endif

  /**
   * @param errnum - the error number
   * @return error string corresponding to errnum
   */
  static const char* strerror(int errnum);

  /**
   * @return -1 if failed to submit log messages to backend system.
   */
  int log(int level, const char* msg);

private:

// OPERATIONS

// ATTRIBUTES

#if defined(x86)
  std::shared_ptr<spdlog::logger> logger_;
#elif defined(avr)
  Stream& logger_;
#elif defined(stm32)
#endif
};

} // namespace log

} // namespace btr

#endif // _btr_log_LoggerImpl_hpp_
