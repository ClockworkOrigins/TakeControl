SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/redskiesascensiondemoplugin)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE RSADemoSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE RSADemoHeader ${includedir}/*.h)

ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)

ADD_LIBRARY(RSADemoPlugin SHARED ${RSADemoSrc} ${RSADemoHeader})

target_link_libraries(RSADemoPlugin ${QT_LIBRARIES})

set_target_properties(
	RSADemoPlugin PROPERTIES FOLDER Plugins
)

set_target_properties(
	RSADemoPlugin PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/game
	RSADemoPlugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/game
	RSADemoPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins/game
	RSADemoPlugin PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/game
	RSADemoPlugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/game
	RSADemoPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins/game
)
