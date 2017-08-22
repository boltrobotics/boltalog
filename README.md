## Purpose
The project enables to:

* Document program events (logs and metrics) using XML model
* Generate strongly-typed, C++ interface for reporting the events via syslog
* Generate Python script for viewing the events in a user-friendly format

## Dependencies
* [GSL Universal Code Generator](https://github.com/imatix/gsl)
* [Googletest](https://github.com/google/googletest)
* Ubuntu 16.04 with the latest cmake, g++
* pcre package (e.g. libpcre3-dev)

## Building
Note: GSL and Goggletest are retrieved and built from github during build process

    git clone git://github.com/svkapustin/strong-log
    mkdir strong-log/build
    cd strong-log/build
    cmake -DLOG_MODEL=model/log_model_example.xml ..
    make
    
    
