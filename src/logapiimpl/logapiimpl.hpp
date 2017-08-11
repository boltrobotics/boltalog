/*
 * License
 */

#ifndef _logger_hpp_
#define _logger_hpp_

#include <cstdint>
#include <array>
#include <memory>

using namespace std;

class logger
{
public:
    enum Severity {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    // OPERATIONS

    static logger* instance();

    bool filter(int id) const;

    void onLogEvent1Impl(
            int32_t param1,
            const string& param2,
            string&& param3);

    void onLogEvent2Impl(
            uint16_t param1,
            const string& param2);

    void onLogEvent3Impl(
            uint64_t p1,
            uint16_t p2,
            string&& p3,
            const string& p4);

private:

    // LIFECYCLE

    logger();

    // ATTRIBUTES

    static unique_ptr<logger> m_Logger;
    array<int, 3> m_Severities;
    int m_Severity;
};

#endif // _logger_hpp_
