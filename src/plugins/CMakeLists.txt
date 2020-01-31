SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/plugins)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE PluginsSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE PluginsHeader ${includedir}/*.h)

ADD_LIBRARY(TCPlugins SHARED ${PluginsSrc} ${PluginsHeader})

target_link_libraries(TCPlugins ${QT_LIBRARIES})

set_target_properties(
	TCPlugins PROPERTIES FOLDER Libraries
)
