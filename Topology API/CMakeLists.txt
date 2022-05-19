cmake_minimum_required(VERSION 3.20)
project(Topology_API)

set(CMAKE_CXX_STANDARD 14)

add_executable(Topology_API main.cpp topology.cpp topology.h json.hpp API.cpp API.h component.cpp component.h Device.cpp Device.h test.cpp test.h)
