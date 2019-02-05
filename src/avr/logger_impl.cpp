// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

// SYSTEM INCLUDES
#include <HardwareSerial.h>

// PROJECT INCLUDES
#include "boltalog/logger_impl.hpp"

namespace btr
{

namespace log
{

#define LOG_ENOBASE   23000
#define EBADLOGLEVEL  (LOG_ENOBASE + 1)

/////////////////////////////////////////////// PUBLIC /////////////////////////////////////////////

//============================================= LIFECYCLE ==========================================

LoggerImpl::LoggerImpl() :
  LoggerImpl(Serial)
{
}

LoggerImpl::LoggerImpl(Stream& logger) :
  logger_(logger)
{
}

//============================================= OPERATIONS =========================================

void setup()
{
}

Stream& LoggerImpl::backend()
{
  return logger_;
}

const char* LoggerImpl::strerror(int errnum)
{
  switch (errnum) {
  case EBADLOGLEVEL:
    return "Bad log level";
  default:
    return "Unknown";
  }
}

int LoggerImpl::log(int level, const char* msg)
{
  (void) level;
  logger_.println(msg);
  return 0;
}

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

} // namespace log

} // namespace btr
