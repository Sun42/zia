cmake_minimum_required(VERSION 2.6)

project(ZiaPluginLoader)

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3")
endif()

set (
  sources
  ./src/main.cpp
  ./src/Packet.cpp
  ./src/NetworkThread.cpp
  ./src/ParserLoader.cpp
  ./src/Preferences.cpp
  ./src/ZiaPluginLoader.cpp
)

set (
  headers
  ./headers/Packet.h
  ./headers/ZiaPluginLoader.h
)

set (
  ui_files
  ./ui/Preferences.ui
  ./ui/ZiaPluginLoader.ui
)

set (
  moc_files
  ./headers/NetworkThread.h
  ./headers/ParserLoader.h
  ./headers/Preferences.h
  ./headers/ZiaPluginLoader.h
)

set (
  res_file
  ./Images.qrc
)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

QT4_ADD_RESOURCES( rc_sources ${res_file} )
QT4_WRAP_UI( ui_headers ${ui_files} )
QT4_WRAP_CPP( sources ${moc_files} )
#QT4_AUTOMOC( moc_sources ${moc_files} )

#include_directories( ${CMAKE_BINARY_DIR} )

add_executable (
  ZiaPluginLoader
  ${sources}
  ${headers}
  ${moc_sources}
  ${rc_sources}
  ${ui_headers}
)

target_link_libraries(
  ZiaPluginLoader
  ${QT_LIBRARIES}
)
