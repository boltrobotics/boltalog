/*
 * License
 */

#define LOGAPI_VERSION_MAJOR @LOGAPI_VERSION_MAJOR@
#define LOGAPI_VERSION_MINOR @LOGAPI_VERSION_MINOR@

#include "logapiimpl.hpp"

/**
 * Log is emitted when so and so occurs.
 */
#define onLogEvent1(p1, p2, p3) \
    if (logger::instance()->filter(0)) { \
        logger::instance()->onLogEvent1Impl(p1, p2, p3); \
    }

/**
 * Log is emitted when so and so occurs.
 */
#define onLogEvent2(param1, param2) \
    if (logger::instance()->filter(1)) { \
        logger::instance()->onLogEvent2Impl(param1, param2); \
    }

/**
 * Log is emitted when so and so occurs.
 */
#define onLogEvent3(p1, p2, p3, p4) \
    if (logger::instance()->filter(3)) { \
        logger::instance()->onLogEvent3Impl(p1, p2, p3, p4); \
    }
