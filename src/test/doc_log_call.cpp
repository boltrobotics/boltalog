#include <gtest/gtest.h>
#include <syslog.h>
#include <iostream>

int log_level_ = LOG_WARNING;

void log(const std::string&) {
    if (LOG_INFO <= log_level_) {
        std::cout << "Event is output" << std::endl;
    }
}

std::string getStuffSlowly() {
    std::string blah = "hmmm... blah blah";

    for (int i = 0; i < 27; i++) {
        blah += blah;
    }
    return blah;
}

TEST(Doc, BadLogCall) {
    log(getStuffSlowly());
}

TEST(Doc, GoodLogCall) {
    if (LOG_INFO <= log_level_) {
        log(getStuffSlowly());
    }
}

#define onLogEvent(slow_stuff) \
    if (LOG_INFO <= log_level_) { \
        log(slow_stuff); \
    }

TEST(Doc, GoodLogCallMacro) {
    onLogEvent(getStuffSlowly());
}
