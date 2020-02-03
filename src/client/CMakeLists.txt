SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/client)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE ClientSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE ClientHeader ${includedir}/*.h)

ADD_EXECUTABLE(TakeControl ${ClientSrc} ${ClientHeader})

target_link_libraries(TakeControl TCPlugins TCProjects ${QT_LIBRARIES})
