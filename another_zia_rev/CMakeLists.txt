cmake_minimum_required(VERSION 2.6)
include(FindBoost)

project(Zia)

if (UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
    set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -rdynamic -ldl")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
  endif()
else (WIN32)
  SET(Boost_LIB_DIAGNOSTIC_DEFINITIONS "-DBOOST_LIB_DIAGNOSTIC")
  SET(CMAKE_INSTALL_PREFIX ".")
endif()

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS   ON)

find_package(Boost 1.39.0 COMPONENTS system thread date_time filesystem REQUIRED)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(includes)
include_directories(includes/zia_api)
include_directories(includes/zia_api/filter)
include_directories(includes/zia_api/http)
include_directories(includes/zia_api/network)
include_directories(${Boost_INCLUDE_DIRS})

file(
  GLOB_RECURSE
  ziaFiles
  src/*.cpp
  includes/*.h
  includes/*.hpp
)

if (UNIX)
  list (REMOVE_ITEM ziaFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/WLoaderLib.cpp")
else (WIN32)
  list (REMOVE_ITEM ziaFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/ULoaderLib.cpp")
endif()

add_executable(Zia ${ziaFiles})

target_link_libraries(
  Zia
  ${Boost_LIBRARIES}
  ${QT_LIBRARIES}
)
