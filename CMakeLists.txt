cmake_minimum_required(VERSION 3.5)
project(boltalog)

set(CMAKE_MODULE_PATH $ENV{PROJECTS_HOME}/cmake-helpers/cmake/Modules)
include(init)
include(firmware)

function(add_target_config_args)
  add_target_config(
    DIRECTORY src/${BOARD_FAMILY}
    TOOLCHAIN_FILE ${TOOLCHAIN_FILE}
    BOARD_FAMILY ${BOARD_FAMILY}
    CMAKE_ARGUMENTS
      -DEXECUTABLE_OUTPUT_PATH=${EXECUTABLE_OUTPUT_PATH}
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DLIBRARY_OUTPUT_PATH=${LIBRARY_OUTPUT_PATH}
      -DBOLTABUS_SOURCE_DIR=${PROJECT_SOURCE_DIR}
      -DBOARD_FAMILY=${BOARD_FAMILY}
      ${ARGN}
  )
endfunction()

string(COMPARE EQUAL "${BOARD_FAMILY}" stm32 _cmp)
if (_cmp)
  set(STM32_CMAKE $ENV{STM32_CMAKE})

  if (NOT STM32_CMAKE)
    message(FATAL_ERROR "STM32_CMAKE directory undefined")
  endif()

  set(TOOLCHAIN_FILE ${STM32_CMAKE}/cmake/gcc_stm32.cmake)
  set(STM32_CHIP $ENV{STM32_CHIP})
  set(STM32_LINKER_SCRIPT $ENV{STM32_LINKER_SCRIPT})
  set(STM32_FLASH_SIZE $ENV{STM32_FLASH_SIZE})
  set(STM32_RAM_SIZE $ENV{STM32_RAM_SIZE})

  add_target_config_args(
    -DTOOLCHAIN_PREFIX=/usr/local
    -DSTM32_CHIP=${STM32_CHIP}
    -DSTM32_LINKER_SCRIPT=${STM32_LINKER_SCRIPT}
    -DSTM32_FLASH_SIZE=${STM32_FLASH_SIZE}
    -DSTM32_RAM_SIZE=${STM32_RAM_SIZE})

  add_target_build(src ${BOARD_FAMILY})
  add_target_flash(src ${BOARD_FAMILY} 0x08000000)
  add_target_flash128(src ${BOARD_FAMILY} 0x08000000)

else ()

  string(COMPARE EQUAL "${BOARD_FAMILY}" x86 _cmp)
  if (_cmp)
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86)
  endif ()

endif ()

####################################################################################################
# unit testing, x86 {

include(unit_testing)

# } unit testing, x86
