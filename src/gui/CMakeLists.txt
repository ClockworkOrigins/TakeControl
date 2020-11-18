SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/gui)

INCLUDE_DIRECTORIES(${includedir})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/nodes)

FILE(GLOB_RECURSE GuiSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE GuiHeader ${includedir}/*.h)

ADD_LIBRARY(TCGui SHARED ${GuiSrc} ${GuiHeader})

target_link_libraries(TCGui TCCore ${QT_LIBRARIES})

set_target_properties(
	TCGui PROPERTIES FOLDER Libraries
)
