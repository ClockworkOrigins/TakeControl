SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/utils)

INCLUDE_DIRECTORIES(${includedir})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/nodes)

FILE(GLOB_RECURSE UtilsSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE UtilsHeader ${includedir}/*.h)

ADD_LIBRARY(TCUtils SHARED ${UtilsSrc} ${UtilsHeader})

target_link_libraries(TCUtils TCNodes ${QT_LIBRARIES})

set_target_properties(
	TCUtils PROPERTIES FOLDER Libraries
)
