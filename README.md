# Overview

Project's requirements:

* Define a log event model of some application
* Auto-generate C++ interface for logging
* Support AVR / STM32 / x86 platforms

Benefits:

* Improve program robustness through strongly-typed interface
* Derive log analysis tools from the model
* Documentat program's behaviour using event description
* Reduce bugs through pre-defined interface/implementation templates
* Reduce typing of similiar code

# Table of Contents

* [Dependencies](#Dependencies)
* [Example](#Example)
  * [Model](#Model)
  * [Generated Code](#Generated_Code)
  * [Program Code](#Program_Code)

<a name="Dependencies"></a>
# Dependencies

The following are top-level dependencies. Depending on target platform additional tools may be
required.<br>
(See [Example](#Example),
<a href="https://github.com/boltrobotics/boltalog/blob/master/src/stm32/CMakeLists.txt" target="_blank">stm32/CMakeLists.txt</a>,
<a href="https://github.com/boltrobotics/boltalog/blob/master/src/avr/CMakeLists.txt" target="_blank">avr/CMakeLists.txt</a>)

* <a href="https://github.com/boltrobotics/cmake-helpers" target="_blank">cmake-helpers</a>
* <a href="https://github.com/boltrobotics/ctpp" target="_blank">ctpp</a>
* <a href="https://github.com/boltrobotics/utility" target="_blank">utility</a>
* <a href="https://github.com/gabime/spdlog" target="_blank">spdlog</a>

<a name="Example"></a>
<h1><a href="https://github.com/boltrobotics/boltalog/tree/master/test" target="_blank">Example</a></h1>

Example log model and code generation is included as part of unit testing. Cmake build instructions
are specified in <a href="https://github.com/boltrobotics/boltalog/blob/master/test/CMakeLists.txt" target="_blank">test/CMakeLists.txt</a>.

<a name="Model"></a>
<h3><a href="https://github.com/boltrobotics/boltalog/blob/master/model/example.mdl" target="_blank">Model</a></h3>

Event model is specified using JSON format:
```javascript
{
'namespace': [ 'test', 'log' ],
'events': [
	...
  {
    'id':'4', 'name':'event4', 'level':'TRACE', 'doc':'Event4 description',
    'params': [
      { 'name':'u8', 'type':'uint8_t', 'doc':'u8 description' },
      { 'name':'d64', 'type':'int64_t' },
      { 'name':'u16', 'type':'uint16_t' },
      { 'name':'d32', 'type':'int32_t' },
      { 'name':'u32', 'type':'uint32_t' },
      { 'name':'d16', 'type':'int16_t' },
      { 'name':'u64', 'type':'uint64_t' },
      { 'name':'d8', 'type':'int8_t' },
      { 'name':'dbl', 'type':'double', 'doc':'dbl description' },
      { 'name':'str', 'type':'string', 'doc':'string description' },
      { 'name':'hx', 'type':'hex', 'doc':'hex description' },
      { 'name':'hx2', 'type':'hex' }
    ]
  }
]
}
```

Array values from ```namespace``` are used to create a C++ namespace for the generated code.
Array ```events``` contains event definitions. Each event is described using the following elements:

* id - numeric event ID
* name - event name that is used as part of API call, e.g. ```onEvent4(...)```
* level - default event log level. Levels range from TRACE to CRITICAL
* doc - event or parameter description. These are added as comments to the code
* params - the array contains parameter specifications. It may be empty. Each parameter is
	specified using:
  * name - parameter name
  * type - parameter type (signed/unsgined integers, double, string, hex binary representation)
  * doc - parameter description

<a name="Generated_Code"></a>
<h3><a href="https://github.com/boltrobotics/boltalog/blob/master/test/logger.hpp" target="_blank">Generated Code</a></h3>

By default, code generator produces three files:

* [logger.hpp](#logger.hpp)
* [logger.cpp](#logger.cpp)
* [log-viewer.py](#log-viewer.py)

<a name="logger.hpp"></a>
<h4><a href="https://github.com/boltrobotics/boltalog/blob/master/test/logger.hpp" target="_blank">logger.hpp</a></h4>

The header file starts with a preample (header guard, platform-specific includes, namespace):
```cpp
#ifndef _test_log_Logger_hpp_
#define _test_log_Logger_hpp_

#if defined(x86)
#include <memory>
namespace spdlog
{
class logger;
}
#elif defined(avr)
class HardwareSerial;
#endif // defined(x86)
...
```

Next follow event macros that first filter an event per its log level, and then invoke actual logging
function implementation:

```cpp
/**
 * Event4 description
 *
 * @param u8 u8 decription
 * ...
 */
#define event4(u8, d64, u16, d32, u32, d16, u64, d8, dbl, str, str_size, hx, hx_size, hx2, hx2_size) \
  if (test::log::Logger::instance()->filter(4)) { \
    test::log::Logger::instance()->event4Impl( \
      u8,d64,u16,d32,u32,d16,u64,d8,dbl,str, str_size,hx, hx_size,hx2, hx2_size); \
  }
```

The rest of the header contains remaining declarations:
```cpp
class Logger {
...
  int event4Impl(...);
...
};
```

<a name="logger.cpp"></a>
<h4><a href="https://github.com/boltrobotics/boltalog/blob/master/test/logger.cpp" target="_blank">logger.cpp</a></h4>

The file implementats functions declared in the header:
```cpp
int Logger::event4Impl(...)
{
  int cx = snprintf(...);
  return log(cx, levels_[4], buff);
}
```

<a name="log-viewer.py"></a>
<h4><a href="https://github.com/boltrobotics/boltalog/blob/master/test/log-viewer.py" target="_blank">log-viewer.py</a></h4>

Generated C++ code outputs logs using CSV format, for example:
```
4,8,64,16,32,32,16,64,8,8.800000,text,74:65,74:65:78
```

The python script prepends parameter name (defined in the model) to each field:
```
event4, u8:8, d64:64, u16:16, d32:32, u32:32, d16:16, u64:64, d8:8, dbl:8.800000, str:text, hx:74:65, hx2:74:65:78
```

<a name="Program_Code"></a>
<h3><a href="https://github.com/boltrobotics/boltalog/blob/master/test/logger_test.cpp" target="_blank">Program Code</a></h3>

An example of program code that uses the generated API is provided in
<a href="https://github.com/boltrobotics/boltalog/blob/master/test/logger_test.cpp" target="_blank">logger_test.cpp</a>.
Excerpt:

```cpp
#include "logger.hpp"

TEST_F(LoggerTest, Output)
{
...
  event4(8, 64, 16, 32, 32, 16, 64, 8, 8.8, "text", 4, "text", 2, "text", 3);
...
}
```
