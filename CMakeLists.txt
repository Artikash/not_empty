cmake_minimum_required(VERSION 2.8)
project(not_empty_tests)

add_executable(Test test.cpp)
set_property(TARGET Test PROPERTY CXX_STANDARD 11)
