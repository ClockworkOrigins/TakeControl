SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/gothic2plugin)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE Gothic2Src ${srcdir}/*.cpp)
FILE(GLOB_RECURSE Gothic2Header ${includedir}/*.h)

ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

ADD_LIBRARY(Gothic2Plugin SHARED ${Gothic2Src} ${Gothic2Header})

target_link_libraries(Gothic2Plugin ${QT_LIBRARIES})
target_link_libraries(Gothic2Plugin TCCore)

set_target_properties(
	Gothic2Plugin PROPERTIES FOLDER Plugins
)

set_target_properties(
	Gothic2Plugin PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/game
	Gothic2Plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/game
	Gothic2Plugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/game
	Gothic2Plugin PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/game
	Gothic2Plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/game
	Gothic2Plugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/game
)
