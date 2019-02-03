// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

#ifndef _btr_log_LoggerImpl_hpp_
#define _btr_log_LoggerImpl_hpp_

// SYSTEM INCLUDES
#if defined(x86)
#include <memory>
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

#if defined(x86)
  /**
   * @param logger - spdlog logger
   */
  LoggerImpl(std::shared_ptr<spdlog::logger> logger);
#endif

  /**
   * Create a stderr console logger as default.
   */
  LoggerImpl();

  /**
   * Deregister the logger instance.
   */
  ~LoggerImpl();

// OPERATIONS

#if defined(x86)
  std::shared_ptr<spdlog::logger> backend();
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
#endif
};

} // namespace log

} // namespace btr

#endif // _btr_log_LoggerImpl_hpp_
