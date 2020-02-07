SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/utils)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE UtilsSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE UtilsHeader ${includedir}/*.h)

ADD_LIBRARY(TCUtils STATIC ${UtilsSrc} ${UtilsHeader})

target_link_libraries(TCUtils ${QT_LIBRARIES})

set_target_properties(
	TCUtils PROPERTIES FOLDER Libraries
)
