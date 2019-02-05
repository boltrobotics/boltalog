// Copyright (C) 2019 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

#ifndef _btr_log_ParamMapper_hpp_
#define _btr_log_ParamMapper_hpp_

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
 * The class encapsulates a set of servers and registers to poll once or periodically.
 */
class ParamMapper : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  ParamMapper() = default;

  /**
   * Dtor.
   */
  ~ParamMapper() = default;;

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

inline INT_32 ParamMapper::Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger)
{
  (void)logger;
  int rc = 0;

  if (argc == 2) {
    const STLW::string n = argv[0].GetString();
    const STLW::string s = argv[1].GetString();

    if (s == "int8_t") {
      cdt = "int8_t " + n;
    } else if (s == "uint8_t") {
      cdt = "uint8_t " + n;
    } else if (s == "int16_t") {
      cdt = "int16_t " + n;
    } else if (s == "uint16_t") {
      cdt = "uint16_t " + n;
    } else if (s == "int32_t") {
      cdt = "int32_t " + n;
    } else if (s == "uint32_t") {
      cdt = "uint32_t " + n;
    } else if (s == "int64_t") {
      cdt = "int64_t " + n;
    } else if (s == "uint64_t") {
      cdt = "uint64_t " + n;
    } else if (s == "double") {
      cdt = "double " + n;
    } else if (s == "string") {
      cdt = "const char* " + n + ", int " + n + "_size";
    } else if (s == "hex") {
      cdt = "const char* " + n + ", int " + n + "_size";
    } else {
      std::string t(
          "int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, "
          "double, string, hex");
      logger.Error("Type unsupported: %s. Supported: %s\n", s.c_str(), t.c_str());
      rc = -1;
    }
  } else {
    logger.Emerg("Usage: PARAMMAPPER(type, name)"); 
    rc = -1;
  }
  return rc;
}

inline CCHAR_P ParamMapper::GetName() const
{
  return "parammapper";
}

} // namespace log

} // namespace btr

#endif // _btr_log_ParamMapper_hpp_
