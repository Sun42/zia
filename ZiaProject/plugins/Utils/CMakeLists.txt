cmake_minimum_required(VERSION 2.6)
include(FindBoost)

project(Utils)

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -rdynamic -ldl")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
endif()

set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.39.0 COMPONENTS system thread filesystem REQUIRED)

include_directories(../../includes/)
include_directories(../../includes/zia_api/)
include_directories(../../includes/zia_api/filter)
include_directories(../../includes/zia_api/http)
include_directories(../../includes/zia_api/network)

include_directories(${Boost_INCLUDE_DIRS})

file(
  GLOB_RECURSE
  sources
  Utils.h
  Utils.cpp
  main.cpp
)

add_executable(Utils ${sources})

target_link_libraries(
  Utils
  ${Boost_LIBRARIES}
)
