Log API generator allows to generate portable, strongly-typed C++ logging API from a model. The
generated code supports AVR / STM32 / x86 platforms.

## Table of Contents
* [Example](#Example)
* [Log Model](#Model)
* [Generated Code](#Generated_Code)
  * [logger.hpp](#logger.hpp)
  * [logger.cpp](#logger.cpp)
  * [log-viewer.py](#log-viewer.py)
* [Program Code](#Program_Code)

## Dependencies

The dependencies and their location is defined in [make.sh]({{ gh }}/make.sh). For better version
control, install them manually.

<a name="Example"></a>
## Example

An example <a href="{{ gh }}//model/boltalog_logger.mdl"> log model</a> and instructions to
generate the API are part of unit testing build. See <a href="{{ gh }}/test/CMakeLists.txt">
test/CMakeLists.txt</a>:

```cmake
include(logger)
set(LOGGER_MODEL_NAME boltalog_logger)
setup_logger(
  ${ROOT_SOURCE_DIR}/model/${LOGGER_MODEL_NAME}.mdl
  SRC_DIR ${CMAKE_BINARY_DIR}/test)
```

<a name="Model"></a>
## Log Model

<a href="{{ gh }}//model/boltalog_logger.mdl">Log model</a> is specified using JSON format:

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

Array values from _namespace_ are used to create a C++ namespace for the generated code.
Array _events_ contains event definitions. Each event is described using the following elements:

* id - numeric event ID
* name - event name that is used as part of API call, e.g. _onEvent4(...)_
* level - default event log level. Levels range from TRACE to CRITICAL
* doc - event or parameter description. These are added as comments to the code
* params - the array contains parameter specifications. It may be empty. Each parameter is
	specified using:
  * name - parameter name
  * type - parameter type (signed/unsigned integers, double, string, hex binary representation)
  * doc - parameter description

<a name="Generated_Code"></a>
## Generated Code

By default, code generator produces three files:

* [logger.hpp](#logger.hpp)
* [logger.cpp](#logger.cpp)
* [log-viewer.py](#log-viewer.py)

Below are given excerpts from the files.

<a name="logger.hpp"></a>
### logger.hpp

The header file starts with a preamble (header guard, platform-specific includes, namespace):
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

Next follow event macros that first filter an event per its log level, and then invoke actual
logging function implementation:

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

A body of the logger class contains actual function declarations:

```cpp
class Logger {
...
  int event4Impl(...);
...
};
```

<a name="logger.cpp"></a>
### logger.cpp

The file contains implementation of the functions which are declared in the header:
```cpp
int Logger::event4Impl(...)
{
  int cx = snprintf(...);
  return log(cx, levels_[4], buff);
}
```

<a name="log-viewer.py"></a>
### log-viewer.py

Generated C++ code outputs logs using CSV format, for example:
```
4,8,64,16,32,32,16,64,8,8.800000,text,74:65,74:65:78
```

The python script inserts names of the parameters, as defined in the model, for better readability:
```
event4, u8:8, d64:64, u16:16, d32:32, u32:32, d16:16, u64:64, d8:8, dbl:8.800000, str:text, hx:74:65, hx2:74:65:78
```

<a name="Program_Code"></a>
## Program Code

An example of program code that uses the generated API is given in
<a href="{{ gh }}/test/logger_test.cpp">logger_test.cpp</a>.
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
