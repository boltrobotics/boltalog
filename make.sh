#!/bin/bash

BOARD_FAMILY="x86"

help()
{
  echo "Usage: `basename $0` [-b (x86 | stm32)] [-h]"
  echo -e "\t-b - board family, default: x86"
  echo -e "\t-h - this help"
}

while getopts "b:h" Option
do
  case $Option in
    b) BOARD_FAMILY=${OPTARG};;
    h) help; exit 0;;
    \?) echo "Invalid option: ${Option}"; exit ${E_OPTERROR};;
  esac
done

# x86

if [ ${BOARD_FAMILY} = "x86" ]; then
  cmake -DBOARD_FAMILY=${BOARD_FAMILY} "$@" .. && make
elif [ ${BOARD_FAMILY} = "stm32" ]; then
  cmake -DBOARD_FAMILY=stm32 -DSTM32_CHIP=stm32f103c8t6 -DSTM32_FLASH_SIZE=64K \
    -DSTM32_RAM_SIZE=20K -DSTM32_LINKER_SCRIPT=stm32f103c8t6.ld "$@" .. && make
else
  echo "Invalid board family: ${BOARD_FAMILY}"
  help
  exit -1
fi
