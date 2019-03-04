// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

/** @file */

#ifndef _btr_log_FormatSpec_hpp_
#define _btr_log_FormatSpec_hpp_

// SYSTEM INCLUDES
#include "CTPP2VMSyscall.hpp"
#include <string>

// PROJECT INCLUDES

namespace btr
{

namespace log
{

using namespace CTPP;

/**
 * The class returns a format specification letter to *printf function given a parameter type.
 */
class FormatSpec : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  FormatSpec() = default;

  /**
   * Dtor.
   */
  ~FormatSpec() = default;;

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

inline INT_32 FormatSpec::Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger)
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
      cdt = "\".6f\"";
    } else if (s == "string") {
      cdt = "\"s\"";
    } else if (s == "hex") {
      cdt = "\"s\"";
    } else {
      std::string t(
          "int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, "
          "double, string, hex");
      logger.Error("Type unsupported: %s. Supported: %s\n", s.c_str(), t.c_str());
      rc = -1;
    }
  } else {
    logger.Emerg("Usage: FORMATSPEC(type)"); 
    rc = -1;
  }
  return rc;
}

inline CCHAR_P FormatSpec::GetName() const
{
  return "formatspec";
}

} // namespace log

} // namespace btr

#endif // _btr_log_FormatSpec_hpp_
