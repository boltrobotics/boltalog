// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

////////////////////////////////////////////////////////////////////////////////////////////////////
// WARNING: The code is auto-generated. Any changes will be overwritten.
////////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <stdio.h>

// PROJECT INCLUDES
#include "logger.hpp" // class implemented
#include "boltalog/defines.hpp"

#if defined(x86)

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
// spdlog appends newline by default. Redefine it in spdlog/include/spdlog/tweakme.h
static auto x86_logger_ = spdlog::stderr_logger_st("std_err");

#elif defined(avr)

#include <HardwareSerial.h>
static Stream* avr_logger_ = &Serial;

#elif defined(stm32)

#include "FreeRTOS.h"
#include "devices/stm32/usb.hpp"

#endif

// AVR libc doesn't define these macros
#if !defined(PRIu64)
#define PRIu64 "llu"
#endif
#if !defined(PRId64)
#define PRId64 "ll"
#endif

namespace test
{

namespace log
{

static Logger logger_;

uint32_t toHex(const char* data, uint32_t size, char* dst_str, uint32_t dst_size)
{
  if (size == 0 || dst_size < (size * 3)) {
    return -1;
  }

  static const char lut[] = "0123456789ABCDEF";
  uint32_t j = 0;

  for (uint32_t i = 0; i < size; i++, j += 3) {
    const uint8_t c = data[i];
    dst_str[j] = lut[c >> 4];
    dst_str[j + 1] = lut[c & 15];
    dst_str[j + 2] = ':';
  }

  if (j >= 3) {
    dst_str[(j - 3) + 2] = '\0';
  }
  return j;
}

/////////////////////////////////////////////// PUBLIC /////////////////////////////////////////////

//============================================= LIFECYCLE ==========================================

Logger::Logger()
{
  levels_[0] = BTR_LOG_LEVEL;

  levels_[1] = btr::log::INFO;
  levels_[2] = btr::log::WARN;
  levels_[3] = btr::log::DEBUG;
  levels_[4] = btr::log::TRACE;
  
}

//============================================= OPERATIONS =========================================

// static
void Logger::init()
{
#if defined(x86)
  // 2017-08-28T11:45:40.523085-04:00
  x86_logger_->set_pattern("%Y-%m-%dT%T.%f%z %L [%t]: %v");
  x86_logger_->set_level(spdlog::level::trace);
#elif defined(stm32)
  btr::Usb::init(true, configMAX_PRIORITIES - 1);
#endif
}

// static
Logger* Logger::instance()
{
  return &logger_;
}

#if defined(x86)
// static 
void Logger::setBackend(std::shared_ptr<spdlog::logger>& backend)
{
  x86_logger_ = backend;
}
#elif defined(avr)
// static 
void Logger::setBackend(Stream& backend)
{
  avr_logger_ = &backend;
}
#endif

// static 
const char* Logger::strerror(int errnum)
{
  switch (errnum) {
  case EBADLOGLEVEL:
    return "Bad log level";
  default:
    return "Unknown";
  }
}

int Logger::level(int event_id, int log_level)
{
  int prev_event_id = -1;

  if (event_id < (int)(sizeof(levels_) / sizeof(int))) {
    prev_event_id = levels_[event_id];
    levels_[event_id] = log_level;
  }
  return prev_event_id;
}

bool Logger::filter(int event_id) const
{
  if (event_id < (int)(sizeof(levels_) / sizeof(int)) && levels_[event_id] >= levels_[0]) {
    return true;
  } else {
    return false;
  }
}

int Logger::event1Impl(
  int32_t param1,
  int8_t param2)
{
  char buff[MAX_LOG_SIZE];
  
  int cx = snprintf(buff, MAX_LOG_SIZE, "1"
    ",%" PRId32 """,%" PRId8 """\r\n",
    param1,param2);

  return log(cx, levels_[1], buff);
}

int Logger::event2Impl(
  uint16_t param1,
  double param2)
{
  char buff[MAX_LOG_SIZE];
  
  int cx = snprintf(buff, MAX_LOG_SIZE, "2"
    ",%" PRIu16 """,%" ".6f" """\r\n",
    param1,param2);

  return log(cx, levels_[2], buff);
}

int Logger::event3Impl(
  uint64_t p1,
  int16_t p2,
  const char* p3, int p3_size,
  uint8_t p4,
  const char* p5, int p5_size)
{
  char buff[MAX_LOG_SIZE];
  
  (void) p3_size;
  char p5_buff[MAX_HEX_SIZE];
  toHex(p5, p5_size, p5_buff, MAX_HEX_SIZE);
  int cx = snprintf(buff, MAX_LOG_SIZE, "3"
    ",%" PRIu64 """,%" PRId16 """,%" "s" """,%" PRIu8 """,%" "s" """\r\n",
    p1,p2,p3,p4,p5_buff);

  return log(cx, levels_[3], buff);
}

int Logger::event4Impl(
  uint8_t u8,
  int64_t d64,
  uint16_t u16,
  int32_t d32,
  uint32_t u32,
  int16_t d16,
  uint64_t u64,
  int8_t d8,
  double dbl,
  const char* str, int str_size,
  const char* hx, int hx_size,
  const char* hx2, int hx2_size)
{
  char buff[MAX_LOG_SIZE];
  
  (void) str_size;
  char hx_buff[MAX_HEX_SIZE];
  toHex(hx, hx_size, hx_buff, MAX_HEX_SIZE);
  char hx2_buff[MAX_HEX_SIZE];
  toHex(hx2, hx2_size, hx2_buff, MAX_HEX_SIZE);
  int cx = snprintf(buff, MAX_LOG_SIZE, "4"
    ",%" PRIu8 """,%" PRId64 """,%" PRIu16 """,%" PRId32 """,%" PRIu32 """,%" PRId16 """,%" PRIu64 """,%" PRId8 """,%" ".6f" """,%" "s" """,%" "s" """,%" "s" """\r\n",
    u8,d64,u16,d32,u32,d16,u64,d8,dbl,str,hx_buff,hx2_buff);

  return log(cx, levels_[4], buff);
}

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

int Logger::log(int cx, int level, const char* msg)
{
  int rc = -1;

  if (cx >= 0) {
#if defined(x86)
    switch (level) {
      case btr::log::TRACE:
        x86_logger_->trace(msg);
        break;
      case btr::log::DEBUG:
        x86_logger_->debug(msg);
        break;
      case btr::log::INFO:
        x86_logger_->info(msg);
        break;
      case btr::log::WARN:
        x86_logger_->warn(msg);
        break;
      case btr::log::ERROR:
        x86_logger_->error(msg);
        break;
      case btr::log::CRITICAL:
        x86_logger_->critical(msg);
        break;
      default:
        errno = EBADLOGLEVEL;
        return rc;
    };
#elif defined(avr)
    (void) level;
    avr_logger_->print(msg);
#elif defined(stm32)
    (void) level;
    btr::Usb::send(msg);
#endif

    if (cx < MAX_LOG_SIZE) {
      rc = 0;
    } else {
      // AVR libc doesn't define EOVERFLOW, just use ERANGE
      errno = ERANGE;
    }
  }
  return rc;
}

} // namespace test

} // namespace log

