# CMake generated Testfile for 
# Source directory: /home/sergey/dev/apps/strong-log.git
# Build directory: /home/sergey/dev/apps/strong-log.git/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(logapi_test "bin/logapi")
subdirs(src/logapiimpl)
subdirs(src/logapi)
