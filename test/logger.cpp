// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

////////////////////////////////////////////////////////////////////////////////////////////////////
// WARNING: The code is auto-generated. Any changes will be overwritten.
////////////////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES

// PROJECT INCLUDES
#include "logger.hpp" // class implemented
#include "boltalog/defines.hpp"
#include "utility/misc.hpp"

#if BTR_LOG_ENABLED > 0

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
#include <avr/pgmspace.h>
#include <string.h>
#include "devices/usart.hpp"
#include "devices/avr/time.hpp"

#elif BTR_STM32 > 0
#define BOLTALOG_EOL() "\r\n"
#include <string.h>
#include "devices/usart.hpp"
#include "devices/stm32/usb.hpp"
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

#if BTR_LOG_ERR_ENABLED > 0
static uint8_t errors_[BTR_ERR_BITS(BTR_LOG_ERR_ENABLED)];
#endif

/////////////////////////////////////////////// PUBLIC /////////////////////////////////////////////

//============================================= LIFECYCLE ==========================================

Logger::Logger()
{
#if BTR_LOG_ENABLED > 0
  levels_[0] = BTR_LOG_LEVEL;

  levels_[1] = btr::log::INFO;
  levels_[2] = btr::log::WARN;
  levels_[3] = btr::log::DEBUG;
  levels_[4] = btr::log::TRACE;
  
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

//--------------------------------------------------------------------------------------------------
// Error state

// static
void Logger::setError(uint8_t err_addr, uint8_t offset)
{
#if BTR_LOG_ERR_ENABLED > 0
  btr::Misc::setBit(errors_, err_addr, offset);
#endif
}

// static
void Logger::clearError(uint8_t err_addr, uint8_t offset)
{
#if BTR_LOG_ERR_ENABLED > 0
  btr::Misc::clearBit(errors_, err_addr, offset);
#endif
}

// static
bool Logger::isError(uint8_t err_addr, uint8_t offset)
{
#if BTR_LOG_ERR_ENABLED > 0
  return btr::Misc::checkBit(errors_, err_addr, offset);
#else
  return false;
#endif
}

// static
bool Logger::isError()
{
#if BTR_LOG_ERR_ENABLED > 0
  for (uint8_t i = 0; i < BTR_ERR_BITS(BTR_LOG_ERR_ENABLED); i++) {
    if (errors_[i] & 0xFF) {
      return true;
    }
  }
#endif
  return false;
}

// static
void Logger::clearErrors()
{
#if BTR_LOG_ERR_ENABLED > 0
  for (uint8_t i = 0; i < BTR_ERR_BITS(BTR_LOG_ERR_ENABLED); i++) {
    errors_[i] = 0;
  }
#endif
}

//--------------------------------------------------------------------------------------------------

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
    case btr::log::TRACE:
      return 'T';
    case btr::log::DEBUG:
      return 'D';
    case btr::log::INFO:
      return 'I';
    case btr::log::WARN:
      return 'W';
    case btr::log::ERROR:
      return 'E';
    case btr::log::CRITICAL:
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
  char buff[MAX_LOG_SIZE];
  
  int cx = snprintf(buff, MAX_LOG_SIZE,
#if BTR_AVR > 0 | BTR_ARD > 0 | BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "1"
    ",%" PRId32 """,%" PRId8 "" BOLTALOG_EOL(),
#if BTR_AVR > 0
    btr::Time::sec(), (btr::Time::millis() % 1000), shortLogLevel(levels_[1]),
#elif BTR_ARD > 0
    (millis() / 1000), (millis() % 1000), shortLogLevel(levels_[1]),
#elif BTR_STM32 > 0 // TODO
    (uint32_t) 0, (uint32_t) 0, shortLogLevel(levels_[1]),
#endif
    param1,param2
    );

  return log(cx, levels_[1], buff);
}

int Logger::event2Impl(
  uint16_t param1,
  double param2)
{
  char buff[MAX_LOG_SIZE];
  
  int cx = snprintf(buff, MAX_LOG_SIZE,
#if BTR_AVR > 0 | BTR_ARD > 0 | BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "2"
    ",%" PRIu16 """,%" ".6f" "" BOLTALOG_EOL(),
#if BTR_AVR > 0
    btr::Time::sec(), (btr::Time::millis() % 1000), shortLogLevel(levels_[2]),
#elif BTR_ARD > 0
    (millis() / 1000), (millis() % 1000), shortLogLevel(levels_[2]),
#elif BTR_STM32 > 0 // TODO
    (uint32_t) 0, (uint32_t) 0, shortLogLevel(levels_[2]),
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
  char buff[MAX_LOG_SIZE];
  
  (void) p3_size;
  char p5_buff[MAX_HEX_SIZE];
  toHex(p5, p5_size, p5_buff, MAX_HEX_SIZE);
  int cx = snprintf(buff, MAX_LOG_SIZE,
#if BTR_AVR > 0 | BTR_ARD > 0 | BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "3"
    ",%" PRIu64 """,%" PRId16 """,%" "s" """,%" PRIu8 """,%" "s" "" BOLTALOG_EOL(),
#if BTR_AVR > 0
    btr::Time::sec(), (btr::Time::millis() % 1000), shortLogLevel(levels_[3]),
#elif BTR_ARD > 0
    (millis() / 1000), (millis() % 1000), shortLogLevel(levels_[3]),
#elif BTR_STM32 > 0 // TODO
    (uint32_t) 0, (uint32_t) 0, shortLogLevel(levels_[3]),
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
  char buff[MAX_LOG_SIZE];
  
  (void) str_size;
  char hx_buff[MAX_HEX_SIZE];
  toHex(hx, hx_size, hx_buff, MAX_HEX_SIZE);
  char hx2_buff[MAX_HEX_SIZE];
  toHex(hx2, hx2_size, hx2_buff, MAX_HEX_SIZE);
  int cx = snprintf(buff, MAX_LOG_SIZE,
#if BTR_AVR > 0 | BTR_ARD > 0 | BTR_STM32 > 0
    "%6lu.%03lu %c [0]: "
#endif
    "4"
    ",%" PRIu8 """,%" PRId64 """,%" PRIu16 """,%" PRId32 """,%" PRIu32 """,%" PRId16 """,%" PRIu64 """,%" PRId8 """,%" ".6f" """,%" "s" """,%" "s" """,%" "s" "" BOLTALOG_EOL(),
#if BTR_AVR > 0
    btr::Time::sec(), (btr::Time::millis() % 1000), shortLogLevel(levels_[4]),
#elif BTR_ARD > 0
    (millis() / 1000), (millis() % 1000), shortLogLevel(levels_[4]),
#elif BTR_STM32 > 0 // TODO
    (uint32_t) 0, (uint32_t) 0, shortLogLevel(levels_[4]),
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
        case btr::log::TRACE:
          backend_->trace(msg);
          break;
        case btr::log::DEBUG:
          backend_->debug(msg);
          break;
        case btr::log::INFO:
          backend_->info(msg);
          break;
        case btr::log::WARN:
          backend_->warn(msg);
          break;
        case btr::log::ERROR:
          backend_->error(msg);
          break;
        case btr::log::CRITICAL:
          backend_->critical(msg);
          break;
        default:
          setError(BTR_LOG_EBADLOGLEVEL, BTR_LOG_ERR_OFFSET);
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
        if (cx > MAX_LOG_SIZE) {
          setError(BTR_LOG_ERANGE, BTR_LOG_ERR_OFFSET);
          return -1;
        }
      } else {
        setError(BTR_LOG_EIO, BTR_LOG_ERR_OFFSET);
        return -1;
      }
    }
  } else {
    setError(BTR_LOG_EINVAL, BTR_LOG_ERR_OFFSET);
    return -1;
  }
  return 0;
}
#endif // BTR_LOG_ENABLED > 0

} // namespace test

} // namespace log

