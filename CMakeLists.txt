cmake_minimum_required (VERSION 3.12.0)

set(CMAKE_CXX_STANDARD 11)

#########################################################################
#########################################################################
#
# Global Build Configuration Options
#
#########################################################################

OPTION(WITH_TESTS "builds with unittests" OFF)

project(TakeControl CXX)

SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_PATCH 0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

INCLUDE(cmake/common.cmake)
INCLUDE(cmake/variables.cmake)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Debug)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Release)

#########################################################################
# Library Section
#########################################################################

INCLUDE(cmake/searchDependencies.cmake)

configure_file(${CMAKE_SOURCE_DIR}/config/Config.h.in ${CMAKE_BINARY_DIR}/include/TakeControlConfig.h @ONLY)

INCLUDE(cmake/addToBinDir.cmake)

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)
INCLUDE_DIRECTORIES(SYSTEM ${CMAKE_CURRENT_BINARY_DIR})

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

ADD_SUBDIRECTORY(src)

IF(WITH_TESTS)
	ENABLE_TESTING()
	
	ADD_SUBDIRECTORY(tests)
ENDIF(WITH_TESTS)
