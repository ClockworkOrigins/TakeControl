SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/core)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE CoreSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE CoreHeader ${includedir}/*.h)

ADD_LIBRARY(TCCore SHARED ${CoreSrc} ${CoreHeader})

target_link_libraries(TCCore ${QT_LIBRARIES})
target_link_libraries(TCCore TCUtils)

set_target_properties(
	TCCore PROPERTIES FOLDER Libraries
)
