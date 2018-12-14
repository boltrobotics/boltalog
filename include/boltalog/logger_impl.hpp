/* Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com> */

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
   * Ctor.
   * @param logger - spdlog logger
   */
  LoggerImpl(std::shared_ptr<spdlog::logger> logger);
#endif

// OPERATIONS

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
