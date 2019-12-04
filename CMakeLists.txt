cmake_minimum_required(VERSION 3.15)
project(ChocAn)

set(CMAKE_CXX_STANDARD 14)

add_executable(ChocAn src/ChocAnMain.cpp
        src/Definition.h
        src/sqlite/sqlite3.c
        src/ChocAnDB.cpp
        src/Operator.cpp
        src/Operator.h
        src/Manager.cpp
        src/Manager.h
        src/User.cpp
        src/User.h
        src/Service.cpp
        src/Service.h)

add_executable(UnitTests test/UnitTest.cpp)

add_executable(ChocAnDB src/ChocAnDB.cpp)

add_executable(test
        test/DBtester.cpp
        test/DBtester.h
        test/UnitTest.cpp
        src/Definition.h
        src/sqlite/sqlite3.c
        src/ChocAnDB.cpp
        src/Operator.cpp
        src/Operator.h
        src/Manager.cpp
        src/Manager.h
        src/User.cpp
        src/User.h
        src/Service.cpp
        src/Service.h)
