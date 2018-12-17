// Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL v3

// SYSTEM INCLUDES
#if defined(x86)
#include <spdlog/spdlog.h>
#endif

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

LoggerImpl::LoggerImpl(std::shared_ptr<spdlog::logger> logger) :
  logger_(logger)
{
  if (logger_) {
    logger_->set_level(spdlog::level::trace);
    // 2017-08-28T11:45:40.523085-04:00
    logger_->set_pattern("%Y-%m-%dT%T.%f%z %L [%t]: %v");
  }
}

LoggerImpl::LoggerImpl() :
  LoggerImpl(spdlog::stderr_logger_st("default"))
{
}

LoggerImpl::~LoggerImpl()
{
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
    return "Unknown";
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
