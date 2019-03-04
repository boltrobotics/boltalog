// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

/** @file */

#ifndef _btr_log_PrepString_hpp_
#define _btr_log_PrepString_hpp_

// SYSTEM INCLUDES
#include "CTPP2VMSyscall.hpp"

// PROJECT INCLUDES

namespace btr
{

namespace log
{

using namespace CTPP;

/**
 * The class prepares a string or hex string when formating input for *printf function.
 */
class PrepString : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  PrepString() = default;

  /**
   * Dtor.
   */
  ~PrepString() = default;;

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

  uint32_t count_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              INLINE
////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////// PRIVATE ////////////////////////////////////////////

//============================================= OPERATIONS =========================================

inline INT_32 PrepString::Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger)
{
  int rc = 0;

  if (argc == 2) {
    const STLW::string var_name = argv[0].GetString();
    const STLW::string var_type = argv[1].GetString();

    if (var_type == "hex") {
      // Convert binary to hex
      cdt = "\n  char " + var_name + "_buff[MAX_HEX_SIZE];\n  "
      "toHex(" + var_name + ", " + var_name + "_size, " + var_name + "_buff, MAX_HEX_SIZE);";
    } else if (var_type == "string") {
      cdt = "\n  (void) " + var_name + "_size;";
    }
  } else {
    logger.Emerg("Usage: PREPSTRING(type, name)"); 
    rc = -1;
  }
  return rc;
}

inline CCHAR_P PrepString::GetName() const
{
  return "prepstring";
}

} // namespace log

} // namespace btr

#endif // _btr_log_PrepString_hpp_
