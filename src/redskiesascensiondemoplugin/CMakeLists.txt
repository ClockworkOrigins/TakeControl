SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/redskiesascensiondemoplugin)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE RSADemoSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE RSADemoHeader ${includedir}/*.h)

ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

ADD_LIBRARY(RSADemoPlugin SHARED ${RSADemoSrc} ${RSADemoHeader})

target_link_libraries(RSADemoPlugin ${QT_LIBRARIES})
