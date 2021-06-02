// Copyright (C) 2019 Sergey Kapustin <kapucin@gmail.com>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

/** @file */

#ifndef _btr_log_FormatParams_hpp_
#define _btr_log_FormatParams_hpp_

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
 * The class returns a parameter name for a *printf function.
 */
class FormatParams : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  FormatParams() = default;

  /**
   * Dtor.
   */
  ~FormatParams() = default;;

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

inline INT_32 FormatParams::Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger)
{
  int rc = 0;

  if (argc == 2) {
    const STLW::string n = argv[0].GetString();
    const STLW::string s = argv[1].GetString();

    if (s == "int8_t") {
      cdt = n;
    } else if (s == "uint8_t") {
      cdt = n;
    } else if (s == "int16_t") {
      cdt = n;
    } else if (s == "uint16_t") {
      cdt = n;
    } else if (s == "int32_t") {
      cdt = n;
    } else if (s == "uint32_t") {
      cdt = n;
    } else if (s == "int64_t") {
      cdt = n;
    } else if (s == "uint64_t") {
      cdt = n;
    } else if (s == "double") {
      cdt = n;
    } else if (s == "string") {
      cdt = n;
    } else if (s == "hex") {
      cdt = n + "_buff";
    } else {
      std::string t(
          "int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, "
          "double, string, hex");
      logger.Error("Type unsupported: %s. Supported: %s\n", s.c_str(), t.c_str());
      rc = -1;
    }
  } else {
    logger.Emerg("Usage: FORMATPARAMS(type, name)"); 
    rc = -1;
  }
  return rc;
}

inline CCHAR_P FormatParams::GetName() const
{
  return "formatparams";
}

} // namespace log

} // namespace btr

#endif // _btr_log_FormatParams_hpp_
