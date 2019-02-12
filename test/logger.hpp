// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

////////////////////////////////////////////////////////////////////////////////////////////////////
// WARNING: The code is auto-generated. Any changes will be overwritten.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _test_log_Logger_hpp_
#define _test_log_Logger_hpp_

#if defined(x86)
#include <memory>

namespace spdlog
{
class logger;
}

#elif defined(avr)

class Stream;

#endif // defined(x86)

// SYSTEM INCLUDES
#define _STDC_FORMAT_MACROS
#include <inttypes.h>

namespace test
{

namespace log
{


/**
 * Event1 description
 *
 * @param param1 
 * @param param2 
 */
#define event1(param1, param2) \
  if (test::log::Logger::instance()->filter(1)) { \
    test::log::Logger::instance()->event1Impl( \
      param1,param2); \
  }


/**
 * Event2 description
 *
 * @param param1 
 * @param param2 
 */
#define event2(param1, param2) \
  if (test::log::Logger::instance()->filter(2)) { \
    test::log::Logger::instance()->event2Impl( \
      param1,param2); \
  }


/**
 * Event3 description
 *
 * @param p1 
 * @param p2 
 * @param p3 
 * @param p4 
 * @param p5 
 */
#define event3(p1, p2, p3, p3_size, p4, p5, p5_size) \
  if (test::log::Logger::instance()->filter(3)) { \
    test::log::Logger::instance()->event3Impl( \
      p1,p2,p3, p3_size,p4,p5, p5_size); \
  }


/**
 * Event4 description
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
 * @param hx hex description
 * @param hx2 
 */
#define event4(u8, d64, u16, d32, u32, d16, u64, d8, dbl, str, str_size, hx, hx_size, hx2, hx2_size) \
  if (test::log::Logger::instance()->filter(4)) { \
    test::log::Logger::instance()->event4Impl( \
      u8,d64,u16,d32,u32,d16,u64,d8,dbl,str, str_size,hx, hx_size,hx2, hx2_size); \
  }

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

  /**
   * Initialize logger backend. The function must be called prior to any others in this class.
   */
  static void init();

  /**
   * @return global logger instance
   */
  static Logger* instance();

#if defined(x86)
  static void setBackend(std::shared_ptr<spdlog::logger>& backend);
#elif defined(avr)
  static void setBackend(Stream& backend);
#endif

  /**
   * @return text description of the error
   */
  static const char* strerror(int errnum);

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
};

} // namespace test

} // namespace log

#endif // _test_log_Logger_hpp_
