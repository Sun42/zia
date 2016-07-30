cmake_minimum_required(VERSION 2.6)

project(pluginTrace)

if (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -O3")
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -rdynamic -ldl")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3")
    set(LIBRARY_OUTPUT_PATH ../../../../libs/${CMAKE_BUILD_TYPE})
  endif()
else (WIN32)
  SET(Boost_LIB_DIAGNOSTIC_DEFINITIONS "-DBOOST_LIB_DIAGNOSTIC")
  SET(CMAKE_INSTALL_PREFIX ".")
  set(LIBRARY_OUTPUT_PATH ../../../libs/${CMAKE_BUILD_TYPE})
endif()

find_package(Boost 1.39.0 COMPONENTS filesystem REQUIRED)

include_directories(../../Utils)
include_directories(../../../includes)
include_directories(../../../includes/zia_api)
include_directories(../../../includes/zia_api/filter)
include_directories(../../../includes/zia_api/http)
include_directories(../../../includes/zia_api/network)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(headers)

file(
  GLOB_RECURSE
  sources
  src/*.cpp
  headers/*.h
  headers/*.hpp
  ../../Utils/Utils.h
  ../../Utils/Utils.cpp
)

add_library(
  pluginTrace
  SHARED
  ${sources}
)
