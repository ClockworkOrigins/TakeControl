cmake_minimum_required (VERSION 3.7.0)

#########################################################################
#########################################################################
#
# Global Build Configuration Options
#
#########################################################################

project(TakeControl CXX)

SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_PATCH 0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

INCLUDE(cmake/common.cmake)
INCLUDE(cmake/variables.cmake)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)

IF(WIN32)
	SET(CMAKE_CXX_FLAGS_DEBUG		"${CMAKE_CXX_FLAGS_DEBUG} /bigobj /D_WIN32_WINNT=0x0501")
	SET(CMAKE_CXX_FLAGS_RELEASE		"${CMAKE_CXX_FLAGS_RELEASE} /DTakeControl_RELEASE /bigobj /D_WIN32_WINNT=0x0501")
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO		"${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj /DQT_FORCE_ASSERTS /D_WIN32_WINNT=0x0501")
	SET(CMAKE_CXX_FLAGS_MINSIZEREL		"${CMAKE_CXX_FLAGS_MINSIZEREL} /bigobj /D_WIN32_WINNT=0x0501")
ENDIF(WIN32)

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

ADD_SUBDIRECTORY(src)
