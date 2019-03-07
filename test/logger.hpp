// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

/** @file */

////////////////////////////////////////////////////////////////////////////////////////////////////
// WARNING: The code is auto-generated. Any changes will be overwritten.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _test_log_Logger_hpp_
#define _test_log_Logger_hpp_

// PROJECT INCLUDES
#include "boltalog/defines.hpp"

#if BTR_X86 > 0

#include <memory>

namespace spdlog
{
class logger;
}

#elif BTR_ARD > 0

class HardwareSerial;

#elif BTR_AVR > 0

namespace btr
{
class Usart;
}

#elif BTR_STM32 > 0

namespace btr
{
class Usb;
class Usart;
}

#endif // x86, avr, ard, stm32

namespace test
{


namespace log
{


#if BTR_LOG_ENABLED > 0
/**
 * Event1 description.
 *
 * @param param1 
 * @param param2 
 */
#define event1(param1, param2) \
  if (test::log::Logger::instance()->filter(1)) { \
    test::log::Logger::instance()->event1Impl( \
      param1,param2); \
  }
#else
#define event1(param1, param2) \
      (void) param1; (void) param2; 

#endif // BTR_LOG_ENABLED > 0

#if BTR_LOG_ENABLED > 0
/**
 * Event2 description.
 *
 * @param param1 
 * @param param2 
 */
#define event2(param1, param2) \
  if (test::log::Logger::instance()->filter(2)) { \
    test::log::Logger::instance()->event2Impl( \
      param1,param2); \
  }
#else
#define event2(param1, param2) \
      (void) param1; (void) param2; 

#endif // BTR_LOG_ENABLED > 0

#if BTR_LOG_ENABLED > 0
/**
 * @param p1 
 * @param p2 
 * @param p3 
 * @param p3_size - string size
 * @param p4 
 * @param p5 
 * @param p5_size - string size
 */
#define event3(p1, p2, p3, p3_size, p4, p5, p5_size) \
  if (test::log::Logger::instance()->filter(3)) { \
    test::log::Logger::instance()->event3Impl( \
      p1,p2,p3, p3_size,p4,p5, p5_size); \
  }
#else
#define event3(p1, p2, p3, p3_size, p4, p5, p5_size) \
      (void) p1; (void) p2; (void) p3; (void) p3_size; (void) p4; (void) p5; (void) p5_size; 

#endif // BTR_LOG_ENABLED > 0

#if BTR_LOG_ENABLED > 0
/**
 * Event4 description.
 *
 * @param u8 u8 description
 * @param d64 
 * @param u16 
 * @param d32 
 * @param u32 
 * @param d16 
 * @param u64 
 * @param d8 
 * @param dbl dbl description
 * @param str string description
 * @param str_size - string size
 * @param hx hex description
 * @param hx_size - string size
 * @param hx2 
 * @param hx2_size - string size
 */
#define event4(u8, d64, u16, d32, u32, d16, u64, d8, dbl, str, str_size, hx, hx_size, hx2, hx2_size) \
  if (test::log::Logger::instance()->filter(4)) { \
    test::log::Logger::instance()->event4Impl( \
      u8,d64,u16,d32,u32,d16,u64,d8,dbl,str, str_size,hx, hx_size,hx2, hx2_size); \
  }
#else
#define event4(u8, d64, u16, d32, u32, d16, u64, d8, dbl, str, str_size, hx, hx_size, hx2, hx2_size) \
      (void) u8; (void) d64; (void) u16; (void) d32; (void) u32; (void) d16; (void) u64; (void) d8; (void) dbl; (void) str; (void) str_size; (void) hx; (void) hx_size; (void) hx2; (void) hx2_size; 

#endif // BTR_LOG_ENABLED > 0

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Logging interface for reporting runtime events and metrics.
 *
 * The events are to be logged through the macros defined above.
 */
class Logger {
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  Logger();

  /**
   * Dtor.
   */
  ~Logger() = default;

// OPERATIONS

#if BTR_X86 > 0

  /**
   * @param backend - new backend logger. Should be supplied first time when instance() is called
   * @return global logger instance
   */
  static Logger* instance(std::shared_ptr<spdlog::logger>* backend = nullptr);

#elif BTR_ARD > 0

  static Logger* instance(HardwareSerial* backend = nullptr);

#elif BTR_AVR > 0

  static Logger* instance(btr::Usart* backend = nullptr);

#elif BTR_STM32 > 0

#if BTR_LOG_PORT_USB > 0
  static Logger* instance(btr::Usb* backend = nullptr);
#elif BTR_LOG_PORT_USART > 0
  static Logger* instance(btr::Usart* backend = nullptr);
#else
  /**
   * No-op logger, added as simple fix for when no USB or USART loggers are specified.
   * @return no-op logger
   */
  static Logger* instance();
#endif // STM32 backend

#endif // BTR_X86 > 0 | BTR_ARD > 0 | BTR_AVR > 0 | BTR_STM32 > 0

  //------------------------------------------------------------------------------------------------
  // Error state

  /**
   * Set error.
   *
   * @param err_addr - address of an error bit (0 - 255)
   * @param offset - address space offset. A system can have more than one subsystems whose error
   *  IDs most likely start at 0. To distinguish errors, use subsytem/address-space offset. The
   *  offsets must be coordinated between the subsystems.
   */
  static void setError(uint8_t err_addr, uint8_t offset);

  /**
   * Clear error.
   *
   * @param err_addr - address of an error bit (0 - 255)
   * @param offset - address space offset
   */
  static void clearError(uint8_t err_addr, uint8_t offset);

  /**
   * Check if an error is set.
   *
   * @param err_addr - address of an error bit (0 - 255)
   * @param offset - address space offset
   * @return true if the error is set, false otherwise
   */
  static bool isError(uint8_t err_addr, uint8_t offset);

  /**
   * Check if any error is set system-wide.
   * @return true if some error is set, false if no errors are set
   */
  static bool isError();

  /**
   * Clear all errors.
   */
  static void clearErrors();

  //------------------------------------------------------------------------------------------------

  /**
   * Set the log level of a given event ID.
   *
   * @param event_id
   * @param log_level
   * @return the previous level of the event or -1 when given event didn't exist
   */
  int level(int event_id, int log_level);

  /**
   * @param event_id - the event ID
   * @return true if event is allowed to pass through, false otherwise
   */
  bool filter(int event_id) const;

  /**
   * @return one letter log level
   */
  int shortLogLevel(int level);

#if BTR_LOG_ENABLED > 0

  //------------------------------------------------------------------------------------------------

  int event1Impl(
    int32_t param1,
    int8_t param2);

  int event2Impl(
    uint16_t param1,
    double param2);

  int event3Impl(
    uint64_t p1,
    int16_t p2,
    const char* p3, int p3_size,
    uint8_t p4,
    const char* p5, int p5_size);

  int event4Impl(
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
    const char* hx2, int hx2_size);

  
private:

// OPERATIONS

  /**
   * Common code for logging.
   *
   * @param cx - characters would be used by log message, which can be more than MAX_LOG_SIZE
   * @param level - log level
   * @param msg - log message
   */
  int log(int cx, int level, const char* msg);

// ATTRIBUTES

  int levels_[5];
#if BTR_X86 > 0
  std::shared_ptr<spdlog::logger> backend_;
#elif BTR_ARD > 0
  HardwareSerial* backend_;
#elif BTR_AVR > 0
  btr::Usart* backend_;
#elif BTR_STM32 > 0
#if BTR_LOG_PORT_USB > 0
  btr::Usb* backend_;
#elif BTR_LOG_PORT_USART > 0
  btr::Usart* backend_;
#endif // BTR_LOG_PORT_*
#endif // BTR_X86, BTR_ARD, BTR_AVR, BTR_STM32

#endif // BTR_LOG_ENABLED > 0
};

} // namespace test

} // namespace log

#endif // _test_log_Logger_hpp_
