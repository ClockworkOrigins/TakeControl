SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/nodes)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE NodesSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE NodesHeader ${includedir}/*.h)

ADD_LIBRARY(TCNodes STATIC ${NodesSrc} ${NodesHeader})

target_link_libraries(TCNodes ${QT_LIBRARIES})
