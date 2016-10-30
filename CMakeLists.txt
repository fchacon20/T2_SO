cmake_minimum_required(VERSION 3.6)
project(T2_SO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES
    programa/Cond.cc
    programa/Cond.h
    programa/Lock.cc
    programa/Lock.h
    programa/sthread.c
    programa/sthread.h
    programa/TrainStation.cpp
    programa/TrainStation.h
    programa/TrainStationMain.cpp)

add_executable(T2_SO ${SOURCE_FILES})