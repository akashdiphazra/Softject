cmake_minimum_required(VERSION 3.14)
project(sentiment_analysis)

set(CMAKE_CXX_STANDARD 20)
include(cmake/dependency.cmake)


find_package(pybind11 REQUIRED)

pybind11_add_module(sentiment_model src/bindings.cpp src/classifier.cpp)
