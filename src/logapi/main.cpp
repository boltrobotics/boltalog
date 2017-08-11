#include "logapi.hpp"

int main(int, char**)
{
    onLogEvent1(32, "param2", "param3");
    onLogEvent2(16, "param2");
    onLogEvent3(64, 8, "param3", "param4");
}
