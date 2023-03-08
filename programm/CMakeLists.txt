cmake_minimum_required(VERSION 3.23)
project(programm)

set(CMAKE_CXX_STANDARD 20)

add_executable(programm main.cpp GroebnerLib/includes/Rational.h GroebnerLib/src/Rational.cpp GroebnerLib/includes/Utils.h GroebnerLib/includes/Modular.h)
