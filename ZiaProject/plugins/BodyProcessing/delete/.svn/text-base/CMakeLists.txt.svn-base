cmake_minimum_required(VERSION 2.6)

project(pluginDelete)


if (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -rdynamic -ldl")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3")
    set(LIBRARY_OUTPUT_PATH ../../../../libs/${CMAKE_BUILD_TYPE})
  endif()
else (WIN32)
  SET(CMAKE_INSTALL_PREFIX ".")
  set(LIBRARY_OUTPUT_PATH ../../../libs/${CMAKE_BUILD_TYPE})
endif()

include_directories(headers)
include_directories(../../Utils)
include_directories(../../../includes)
include_directories(../../../includes/zia_api)
include_directories(../../../includes/zia_api/filter)
include_directories(../../../includes/zia_api/http)
include_directories(../../../includes/zia_api/network)

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
  pluginDelete
  SHARED
  ${sources}
)
