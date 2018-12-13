/* Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com> */

#ifndef _btr_log_PrintfFormatters_hpp_
#define _btr_log_PrintfFormatters_hpp_

// SYSTEM INCLUDES
#include "CTPP2VMSyscall.hpp"

// PROJECT INCLUDES

namespace btr
{

namespace log
{

using namespace CTPP;

/**
 * The class encapsulates a set of servers and registers to poll once or periodically.
 */
class PrintfFormatters : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  PrintfFormatters() = default;

  /**
   * Dtor.
   */
  ~PrintfFormatters() = default;;

private:

  friend class STDLibInitializer;

// OPERATIONS

  /**
   * @see SyscallHandler::Handler
   */
  INT_32 Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger);

  /**
   * @see SyscallHandler::GetName
   */
  CCHAR_P GetName() const;

// ATTRIBUTES

};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              INLINE
////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

inline INT_32 PrintfFormatters::Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger)
{
  (void)logger;
  int rc = 0;

  if (argc == 1) {
    const STLW::string s = argv[0].GetString();

    if (s == "int8_t") {
      cdt = "PRId8";
    } else if (s == "uint8_t") {
      cdt = "PRIu8";
    } else if (s == "int16_t") {
      cdt = "PRId16";
    } else if (s == "uint16_t") {
      cdt = "PRIu16";
    } else if (s == "int32_t") {
      cdt = "PRId32";
    } else if (s == "uint32_t") {
      cdt = "PRIu32";
    } else if (s == "int64_t") {
      cdt = "PRId64";
    } else if (s == "uint64_t") {
      cdt = "PRIu64";
    } else if (s == "double") {
      cdt = "\"f\"";
    } else if (s == "string") {
      cdt = "\"s\"";
    } else {
      rc = -1;
    }
  } else {
    rc = -1;
  }
  return rc;
}

inline CCHAR_P PrintfFormatters::GetName() const
{
  return "printfformatter";
}

} // namespace log

} // namespace btr

#endif // _btr_log_PrintfFormatters_hpp_
