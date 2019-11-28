cmake_minimum_required(VERSION 3.15)
project(ChocAn)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChocAn src/ChocAnMain.cpp)

add_executable(UnitTests test/UnitTest.cpp)

add_executable(ChocAnDB src/ChocAnDB.cpp)

add_executable(test
        src/sqlite/sqlite3.c
        test/DBtester.cpp
        test/DBtester.h
        src/ChocAnDB.cpp
        test/UnitTest.cpp
        src/Operator.cpp)
