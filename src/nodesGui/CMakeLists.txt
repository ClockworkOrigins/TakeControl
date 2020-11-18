SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/nodesGui)

INCLUDE_DIRECTORIES(${includedir})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/nodes)

FILE(GLOB_RECURSE NodesGuiSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE NodesGuiHeader ${includedir}/*.h)

ADD_LIBRARY(TCNodesGui SHARED ${NodesGuiSrc} ${NodesGuiHeader})

target_link_libraries(TCNodesGui TCNodes TCUtils ${QT_LIBRARIES})

set_target_properties(
	TCNodesGui PROPERTIES FOLDER Libraries
)
