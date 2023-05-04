cmake_minimum_required(VERSION 3.23)
project(programm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(programm main.cpp GroebnerLib/src/Rational.cpp GroebnerLib/src/Monom.cpp)
