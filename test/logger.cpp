// Copyright (C) 2019 Sergey Kapustin <kapucin@gmail.com>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

////////////////////////////////////////////////////////////////////////////////////////////////////
// WARNING: The code is auto-generated. Any changes will be overwritten.
////////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES

// PROJECT INCLUDES
#include "logger.hpp" // class implemented
#include "boltalog/defines.hpp"
#include "utility/defines.hpp"
#include "utility/misc.hpp"

namespace btr
{
namespace log
{
#if BTR_STATUS_ENABLED > 0
static uint32_t status_;

uint32_t* status()
{
  return &status_;
}
#else
uint32_t* status()
{
  return nullptr;
}
#endif // BTR_STATUS_ENABLED > 0
} // namespace log
} // namespace btr

#if BTR_LOG_ENABLED > 0

#include "devices/defines.hpp"

#if BTR_X86 > 0
#define BOLTALOG_EOL() ""
#include "spdlog/spdlog.h"
#define PROGMEM

#elif BTR_ARD > 0
#define BOLTALOG_EOL() "\r\n"
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <string.h>

#elif BTR_AVR > 0
#define BOLTALOG_EOL() "\r\n"
#include "devices/time.hpp"
#include "devices/usart.hpp"
#include <avr/pgmspace.h>
#include <string.h>

#elif BTR_STM32 > 0
#define BOLTALOG_EOL() "\r\n"
#include "devices/time.hpp"
#include "devices/usart.hpp"
#include "devices/stm32/usb.hpp"
#include <string.h>
#define PROGMEM
#endif // x86, ard, avr, stm32

// AVR libc doesn't define these macros
#if !defined(PRIu64)
#define PRIu64 "llu"
#endif
#if !defined(PRId64)
#define PRId64 "ll"
#endif

// SYSTEM INCLUDES
#include <stdio.h>

#endif // BTR_LOG_ENABLED > 0

namespace test
{

namespace log
{

//==================================================================================================

#if BTR_LOG_ENABLED > 0

static Logger logger_;
static const char lut[] = "0123456789ABCDEF";

uint32_t toHex(const char* src_str, uint32_t src_size, char* dst_str, uint32_t dst_size)
{
  // Includes null character.
  uint32_t total_size = src_size * 3;

  if (src_size == 0 || dst_size < total_size) {
    return -1;
  }

  for (uint32_t i = 0, j = 0; i < src_size; i++, j += 3) {
    const uint8_t c = src_str[i];
    dst_str[j] = lut[c >> 4];
    dst_str[j + 1] = lut[c & 0xF];

    if ((i + 1) < src_size) {
      dst_str[j + 2] = ':';
    }
  }
  dst_str[total_size - 1] = '\0';
  return total_size;
}

#endif // BTR_LOG_ENABLED > 0

//==================================================================================================

/////////////////////////////////////////////// PUBLIC /////////////////////////////////////////////

//============================================= LIFECYCLE ==========================================

Logger::Logger()
{
#if BTR_LOG_ENABLED > 0
  levels_[0] = BTR_LOG_LEVEL_DFLT;

  levels_[1] = btr::INFO;
  levels_[2] = btr::WARN;
  levels_[3] = btr::DEBUG;
  levels_[4] = btr::TRACE;
  
#endif // BTR_LOG_ENABLED > 0
}

//============================================= OPERATIONS =========================================

// static
#if BTR_X86 > 0
Logger* Logger::instance(std::shared_ptr<spdlog::logger>* backend)
{
#if BTR_LOG_ENABLED > 0
  if (nullptr != backend) {
    logger_.backend_ = *backend;
  }
  return &logger_;
#else
  (void) backend;
  return nullptr;
#endif // BTR_LOG_ENABLED > 0
}

#elif BTR_ARD > 0

Logger* Logger::instance(HardwareSerial* backend)
{
#if BTR_LOG_ENABLED > 0
  if (nullptr != backend) {
    logger_.backend_ = backend;
  }
  return &logger_;
#else
  (void) backend;
  return nullptr;
#endif // BTR_LOG_ENABLED > 0
}

#elif BTR_AVR > 0

Logger* Logger::instance(btr::Usart* backend)
{
#if BTR_LOG_ENABLED > 0
  if (nullptr != backend) {
    logger_.backend_ = backend;
  }
  return &logger_;
#else
  (void) backend;
  return nullptr;
#endif // BTR_LOG_ENABLED > 0
}

#elif BTR_STM32 > 0

#if BTR_LOG_PORT_USB > 0
Logger* Logger::instance(btr::Usb* backend)
{
#if BTR_LOG_ENABLED > 0
  if (nullptr != backend) {
    logger_.backend_ = backend;
  }
  return &logger_;
#else
  (void) backend;
  return nullptr;
#endif // BTR_LOG_ENABLED > 0
}

#elif BTR_LOG_PORT_USART > 0
Logger* Logger::instance(btr::Usart* backend)
{
#if BTR_LOG_ENABLED > 0
  if (nullptr != backend) {
    logger_.backend_ = backend;
  }
  return &logger_;
#else
  (void) backend;
  return nullptr;
#endif // BTR_LOG_ENABLED > 0
}

#else // BTR_LOG_PORT_USB0 == 0 && BTR_LOG_PORT_USART == 0
Logger* Logger::instance()
{
#if BTR_LOG_ENABLED > 0
  return &logger_;
#else
  return nullptr;
#endif // BTR_LOG_ENABLED > 0
}
#endif

#endif // BTR_X86, BTR_ARD, BTR_AVR, BTR_STM32

int Logger::level(int event_id, int log_level)
{
#if BTR_LOG_ENABLED > 0
  int prev_event_id = -1;

  if (event_id < (int)(sizeof(levels_) / sizeof(int))) {
    prev_event_id = levels_[event_id];
    levels_[event_id] = log_level;
  }
  return prev_event_id;
#else
  (void) event_id; (void) log_level;
  return -1;
#endif // BTR_LOG_ENABLED > 0
}

bool Logger::filter(int event_id) const
{
#if BTR_LOG_ENABLED > 0
  if (event_id < (int)(sizeof(levels_) / sizeof(int)) && levels_[event_id] >= levels_[0]) {
    return true;
  } else {
    return false;
  }
#else
  (void) event_id;
  return false;
#endif // BTR_LOG_ENABLED > 0
}

int Logger::shortLogLevel(int level)
{
  switch (level) {
    case btr::TRACE:
      return 'T';
    case btr::DEBUG:
      return 'D';
    case btr::INFO:
      return 'I';
    case btr::WARN:
      return 'W';
    case btr::ERROR:
      return 'E';
    case btr::CRITICAL:
      return 'C';
    default:
      return 'O';
  }
}

#if BTR_LOG_ENABLED > 0
int Logger::event1Impl(
  int32_t param1,
  int8_t param2)
{
  char buff[BTR_LOG_MAX];
  
  int cx = snprintf(buff, BTR_LOG_MAX,
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "test:log:1"
    ",%" PRId32 """,%" PRId8 "" BOLTALOG_EOL(),
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    SEC(), (MILLIS() % 1000), shortLogLevel(levels_[1]),
#endif
    param1,param2
    );

  return log(cx, levels_[1], buff);
}

int Logger::event2Impl(
  uint16_t param1,
  double param2)
{
  char buff[BTR_LOG_MAX];
  
  int cx = snprintf(buff, BTR_LOG_MAX,
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "test:log:2"
    ",%" PRIu16 """,%" ".6f" "" BOLTALOG_EOL(),
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    SEC(), (MILLIS() % 1000), shortLogLevel(levels_[2]),
#endif
    param1,param2
    );

  return log(cx, levels_[2], buff);
}

int Logger::event3Impl(
  uint64_t p1,
  int16_t p2,
  const char* p3, int p3_size,
  uint8_t p4,
  const char* p5, int p5_size)
{
  char buff[BTR_LOG_MAX];
  
  (void) p3_size;
  char p5_buff[BTR_LOG_MAX_HEX];
  toHex(p5, p5_size, p5_buff, BTR_LOG_MAX_HEX);
  int cx = snprintf(buff, BTR_LOG_MAX,
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "test:log:3"
    ",%" PRIu64 """,%" PRId16 """,%" "s" """,%" PRIu8 """,%" "s" "" BOLTALOG_EOL(),
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    SEC(), (MILLIS() % 1000), shortLogLevel(levels_[3]),
#endif
    p1,p2,p3,p4,p5_buff
    );

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
  char buff[BTR_LOG_MAX];
  
  (void) str_size;
  char hx_buff[BTR_LOG_MAX_HEX];
  toHex(hx, hx_size, hx_buff, BTR_LOG_MAX_HEX);
  char hx2_buff[BTR_LOG_MAX_HEX];
  toHex(hx2, hx2_size, hx2_buff, BTR_LOG_MAX_HEX);
  int cx = snprintf(buff, BTR_LOG_MAX,
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "test:log:4"
    ",%" PRIu8 """,%" PRId64 """,%" PRIu16 """,%" PRId32 """,%" PRIu32 """,%" PRId16 """,%" PRIu64 """,%" PRId8 """,%" ".6f" """,%" "s" """,%" "s" """,%" "s" "" BOLTALOG_EOL(),
#if BTR_AVR > 0 || BTR_ARD > 0 || BTR_STM32 > 0
    SEC(), (MILLIS() % 1000), shortLogLevel(levels_[4]),
#endif
    u8,d64,u16,d32,u32,d16,u64,d8,dbl,str,hx_buff,hx2_buff
    );

  return log(cx, levels_[4], buff);
}

#endif // BTR_LOG_ENABLED > 0

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

#if BTR_LOG_ENABLED > 0

int Logger::log(int cx, int level __attribute((unused)), const char* msg)
{
  uint32_t rc = 0;

  if (nullptr != backend_) {
    if (cx >= 0) {
#if BTR_X86 > 0
      switch (level) {
        case btr::TRACE:
          backend_->trace(msg);
          break;
        case btr::DEBUG:
          backend_->debug(msg);
          break;
        case btr::INFO:
          backend_->info(msg);
          break;
        case btr::WARN:
          backend_->warn(msg);
          break;
        case btr::ERROR:
          backend_->error(msg);
          break;
        case btr::CRITICAL:
          backend_->critical(msg);
          break;
        default:
          btr::set_status(btr::log::status(), BTR_LOG_EBADLOGLEVEL);
          return -1;
      };
#elif BTR_ARD > 0
      backend_->print(msg);
#elif BTR_AVR > 0
      rc = backend_->send(msg, strlen(msg));
#elif BTR_STM32 > 0
#if BTR_LOG_PORT_USB > 0 || BTR_LOG_PORT_UART > 0
      rc = backend_->send(msg, strlen(msg));
#else
      rc = BTR_LOG_EINVAL;
#endif // BTR_LOG_PORT_USB > 0 || BTR_LOG_PORT_UART > 0
#endif // BTR_X86 > 0 | BTR_ARD > 0 | BTR_AVR > 0 | BTR_STM32 > 0

      if (0 == (rc & 0xFFFF0000)) {
        if (cx > BTR_LOG_MAX) {
          btr::set_status(btr::log::status(), BTR_LOG_ERANGE);
          return -1;
        }
      } else {
        btr::set_status(btr::log::status(), BTR_LOG_EIO);
        return -1;
      }
    }
  } else {
    btr::set_status(btr::log::status(), BTR_LOG_EINVAL);
    return -1;
  }
  return 0;
}
#endif // BTR_LOG_ENABLED > 0

} // namespace test

} // namespace log

