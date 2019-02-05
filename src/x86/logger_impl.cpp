// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

// SYSTEM INCLUDES
#include <spdlog/spdlog.h>

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
  LoggerImpl(spdlog::stderr_logger_st("default"))
{
}

LoggerImpl::LoggerImpl(std::shared_ptr<spdlog::logger> logger) :
  logger_(logger)
{
  if (logger_) {
    logger_->set_level(spdlog::level::trace);
    // 2017-08-28T11:45:40.523085-04:00
    logger_->set_pattern("%Y-%m-%dT%T.%f%z %L [%t]: %v");
  }
}

//============================================= OPERATIONS =========================================

std::shared_ptr<spdlog::logger> LoggerImpl::backend()
{
  return logger_;
}

const char* LoggerImpl::strerror(int errnum)
{
  switch (errnum) {
  case EBADLOGLEVEL:
    return "Bad log level";
  default:
    return strerror(errnum);
  }
}

int LoggerImpl::log(int level, const char* msg)
{
  switch (level) {
  case TRACE:
    logger_->trace(msg);
    break;
  case DEBUG:
    logger_->debug(msg);
    break;
  case INFO:
    logger_->info(msg);
    break;
  case WARN:
    logger_->warn(msg);
    break;
  case ERROR:
    logger_->error(msg);
    break;
  case CRITICAL:
    logger_->critical(msg);
    break;
  default:
    errno = EBADLOGLEVEL;
    return -1;
  };
  return 0;
}

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

} // namespace log

} // namespace btr
