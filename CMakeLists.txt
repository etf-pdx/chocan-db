cmake_minimum_required(VERSION 3.15)
project(ChocAn)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChocAn src/ChocAnMain.cpp)

add_executable(UnitTests test/UnitTest.cpp)
