cmake_minimum_required(VERSION 2.6)

project(pluginAllow)

if (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -rdynamic -ldl")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3")
    set(LIBRARY_OUTPUT_PATH ../../../../libs/${CMAKE_BUILD_TYPE})
  endif()
else (WIN32)
  SET(Boost_LIB_DIAGNOSTIC_DEFINITIONS "-DBOOST_LIB_DIAGNOSTIC")
  SET(CMAKE_INSTALL_PREFIX ".")
  set(LIBRARY_OUTPUT_PATH ../../../libs/${CMAKE_BUILD_TYPE})
endif()

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.39.0 REQUIRED COMPONENTS)


include_directories(../../../includes/)
include_directories(../../../includes/zia_api/)
include_directories(../../../includes/zia_api/filter)
include_directories(../../../includes/zia_api/http)
include_directories(../../../includes/zia_api/network)


include_directories(headers)
include_directories(${Boost_INCLUDE_DIRS})

file(
  GLOB_RECURSE
  sources
  src/*.cpp
  headers/*.h
  headers/*.hpp
)

add_library(
  pluginAllow
  SHARED
  ${sources}
)

target_link_libraries(pluginAllow ${Boost_LIBRARIES})
