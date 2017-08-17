#include "logapiimpl.hpp"
#include <iostream>

unique_ptr<logger> logger::m_Logger;

logger* logger::instance()
{
    if (!m_Logger) {
        m_Logger.reset(new logger);
    }
    return m_Logger.get();
}

logger::logger() :
    m_Severities(),
    m_Severity(DEBUG)
{
    m_Severities[0] = INFO;
    m_Severities[1] = WARNING;
    m_Severities[2] = TRACE;
}

bool logger::filter(int id) const
{
    int severity = m_Severities[id];

    if (severity >= m_Severity) {
        return true;
    } else {
        return false;
    }
}

void logger::onLogEvent1Impl(
        int32_t param1,
        const string& param2,
        string&& param3)
{
    std::cout
        << 0 << ","
        << param1 << ","
        << param2 << ","
        << param3
        << std::endl;
}

void logger::onLogEvent2Impl(
        uint16_t param1,
        const string& param2)
{
    std::cout
        << 1 << ","
        << param1 << ","
        << param2
        << std::endl;
}

void logger::onLogEvent3Impl(
        uint64_t p1,
        uint16_t p2,
        string&& p3,
        const string& p4)
{
    std::cout
        << 2 << ","
        << p1 << ","
        << p2 << ","
        << p3 << ","
        << p4
        << std::endl;
}
