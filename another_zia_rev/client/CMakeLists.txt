cmake_minimum_required(VERSION 2.6)
include(FindBoost)

project(client)

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -g3")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -rdynamic -ldl")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3")
endif()


find_package(
  Boost
  1.39.0
  COMPONENTS system thread filesystem REQUIRED
)

include_directories(${Boost_INCLUDE_DIRS})

set(Boost_USE_MULTITHREADED ON)

file(
  GLOB_RECURSE
  ziaFiles
  client.cpp
)

add_executable(client ${ziaFiles})

target_link_libraries(
  client
  ${Boost_LIBRARIES}
)
