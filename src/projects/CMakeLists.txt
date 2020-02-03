SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/projects)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE ProjectsSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE ProjectsHeader ${includedir}/*.h)

ADD_LIBRARY(TCProjects STATIC ${ProjectsSrc} ${ProjectsHeader})

target_link_libraries(TCProjects ${QT_LIBRARIES})

set_target_properties(
	TCProjects PROPERTIES FOLDER Libraries
)
