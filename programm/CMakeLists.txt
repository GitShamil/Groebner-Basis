cmake_minimum_required(VERSION 3.23)
project(programm)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib/googletest-main)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(lib/googletest-main/googletest/include)

add_executable(programm GroebnerLib/src/Rational.cpp GroebnerLib/src/Monom.cpp tests/RationalTest.cpp
        tests/ModularTest.cpp tests/MonomTest.cpp tests/TermTest.cpp tests/PolynomTest.cpp tests/OrderingTermTest.cpp tests/PolynomSetTest.cpp tests/AlgorithmTest.cpp)
target_link_libraries(programm gtest gtest_main)
