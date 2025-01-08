#!/bin/bash

################################################################################
# Dependency paths

if [ -z ${PROJECTS_HOME} ]; then
  # Assume the script is invoked from within its project.
  export PROJECTS_HOME="${PWD}/.."
fi
if [ -z ${VENDOR_HOME} ]; then
  export VENDOR_HOME=${PROJECTS_HOME}/vendor
fi

# Own projects

if [ -z ${CMAKEHELPERS_HOME} ]; then
  export CMAKEHELPERS_HOME=${PROJECTS_HOME}/cmake-helpers
fi
if [ -z ${UTILITY_HOME} ]; then
  export UTILITY_HOME=${PROJECTS_HOME}/utility
fi
if [ -z ${BOLTALOG_HOME} ]; then
  export BOLTALOG_HOME=${PROJECTS_HOME}/boltalog
fi

# Third-party projects

if [ -z ${CTPP2_HOME} ]; then
  export CTPP2_HOME=${VENDOR_HOME}/ctpp
fi
if [ -z ${GTEST_HOME} ]; then
  export GTEST_HOME=${VENDOR_HOME}/gtest
fi
if [ -z ${FREERTOS_HOME} ]; then
  export FREERTOS_HOME=${VENDOR_HOME}/FreeRTOSv10.1.1
fi
if [ -z ${LIBOPENCM3_HOME} ]; then
  export LIBOPENCM3_HOME=${VENDOR_HOME}/libopencm3
fi
if [ -z ${SPDLOG_HOME} ]; then
  export SPDLOG_HOME=${VENDOR_HOME}/spdlog
fi

################################################################################
# Functions

function clone_impl
{
  echo "Checking $(basename $1)"
  echo -e "  Source: $2"
  echo -e "  Target: $1"

  if [ -d ${1} ]; then
    (cd ${1} && git pull)
  else
    git clone $2 ${1}
  fi
}

function clone()
{
  clone_impl "https://github.com/google/googletest.git" "${GTEST_HOME}" 
  clone_impl "https://github.com/libopencm3/libopencm3.git" "${LIBOPENCM3_HOME}" 
  clone_impl "https://github.com/FreeRTOS/FreeRTOS-Kernel.git" "${FREERTOS_HOME}" 
}

# Process command-line options

x86=0; avr=0; stm32=0; esp32=0;
TESTS=""
VERBOSE=""
COMPILELOG=""
DEBUG=""

function build()
{
  (set -x && \
    cd ${BOLTALOG_HOME} \
    && mkdir -p build-${1} && cd build-${1} \
    && cmake -G Ninja -DBTR_${1^^}=1${TESTS}${VERBOSE}${COMPILELOG}${DEBUG} ${2}  .. \
    && cmake --build . \
  )
}

help()
{
  echo -e "Usage: `basename $0` [-x] [-a] [-s] [-e] [-d] [-c] [-v] [-t] [-h]"
  echo -e "  -a - build avr"
  echo -e "  -e - build esp32"
  echo -e "  -s - build stm32"
  echo -e "  -x - build x86"
  echo -e "  -d - clone or pull dependencies"
  echo -e "  -g - enable debug build"
  echo -e "  -c - export compile commands"
  echo -e "  -v - enable verbose output"
  echo -e "  -t - enable unit tests"
  echo -e "  -h - this help"
}

while getopts "xsadgcvth" Option
do
  case $Option in
    a) avr=1;;
    e) esp32=1;;
    s) stm32=1;;
    x) x86=1;;
    d) clone;;
    g) DEBUG=" -DCMAKE_BUILD_TYPE=Debug";;
    c) COMPILELOG=" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON";;
    v) VERBOSE="-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON";;
    t) x86=1; TESTS=" -DENABLE_TESTS=ON";;
    h) help; exit 0;;
    \?) help; exit 22;;
  esac
done

shift $(($OPTIND - 1))

if [ ${x86} -eq 1 ]; then build x86 " $@"; fi
if [ ${avr} -eq 1 ]; then build avr " $@"; fi
if [ ${stm32} -eq 1 ]; then build stm32 " $@"; fi
if [ ${esp32} -eq 1 ]; then build esp32 " $@"; fi
