/* Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com> */

// SYSTEM INCLUDES

// PROJECT INCLUDES
#include "boltalog/logger_impl.hpp"

namespace btr
{

namespace log
{

/////////////////////////////////////////////// PUBLIC /////////////////////////////////////////////

//============================================= LIFECYCLE ==========================================

LoggerImpl::LoggerImpl() :
  logger_()
{
}

LoggerImpl::~LoggerImpl()
{
}

//============================================= OPERATIONS =========================================

const char* LoggerImpl::strerror(int errnum)
{
  (void)errnum;
  //return Device::strerror(errnum);
  return nullptr;
}

int LoggerImpl::log(int level, const char* msg)
{
  switch (level) {
  case TRACE:
    logger_->trace(msg); break;
  case DEBUG:
    logger_->debug(msg); break;
  case INFO:
    logger_->info(msg); break;
  case WARN:
    logger_->warn(msg); break;
  case ERROR:
    logger_->error(msg); break;
  case CRITICAL:
    logger_->critical(msg); break;
  default:
    return -1;
  };
  return 0;
}

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

} // namespace log

} // namespace btr
