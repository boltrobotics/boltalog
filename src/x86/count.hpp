// Copyright (C) 2019 Sergey Kapustin <kapucin@gmail.com>

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

/** @file */

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
 * The class counts an occurance of a token and may provide the total count.
 */
class Count : public SyscallHandler
{
public:

// LIFECYCLE

  /**
   * Ctor.
   */
  Count();

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


//============================================= LIFECYCLE  =========================================

Count::Count()
  :
    count_(0)
{
}

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
