SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/client)

INCLUDE_DIRECTORIES(${includedir})

# Translation files
SET(TRANS
	${CMAKE_SOURCE_DIR}/languages/de_DE.ts
	${CMAKE_SOURCE_DIR}/languages/en_US.ts
)

FILE(GLOB_RECURSE ClientSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE ClientHeader ${includedir}/*.h)

# add translations ...
QT5_ADD_TRANSLATION(QT_TRANSLATION_FILES ${TRANS})

ADD_EXECUTABLE(TakeControl ${ClientSrc} ${ClientHeader} ${QT_TRANSLATION_FILES})

target_link_libraries(TakeControl TCPlugins TCProjects TCUtils ${QT_LIBRARIES})
