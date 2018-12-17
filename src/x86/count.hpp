// Copyright (C) 2018 Bolt Robotics <info@boltrobotics.com>
// License: GNU GPL v3

#ifndef _btr_log_Count_hpp_
#define _btr_log_Count_hpp_

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
class Count : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  Count() = default;

  /**
   * Dtor.
   */
  ~Count() = default;;

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

inline INT_32 Count::Handler(CDT* argv, const UINT_32 argc, CDT& cdt, Logger& logger)
{
  (void)logger;
  int rc = 0;

  if (argc == 0) {
    cdt = count_;
  } else if (argc == 1) {
    UINT_32 num = argv[0].GetInt();
    count_ += num;
  } else {
    rc = -1;
  }
  return rc;
}

inline CCHAR_P Count::GetName() const
{
  return "count";
}

} // namespace log

} // namespace btr

#endif // _btr_log_Count_hpp_
