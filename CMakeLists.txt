cmake_minimum_required(VERSION 3.26)
project(farcast)

set(CMAKE_CXX_STANDARD 20)

add_executable(farcast main.cpp StatManager.cpp StatManager.h GameStatistics.cpp GameStatistics.h include/httplib.h)
