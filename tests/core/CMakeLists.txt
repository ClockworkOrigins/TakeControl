SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/core)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE CoreTestsSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE CoreTestsHeader ${includedir}/*.h)

ADD_EXECUTABLE(CoreTests ${CoreTestsSrc} ${CoreTestsGuiHeader})

target_link_libraries(CoreTests debug ${GTEST_DEBUG_LIBRARIES} optimized ${GTEST_RELEASE_LIBRARIES})
target_link_libraries(CoreTests ${QT_LIBRARIES})
target_link_libraries(CoreTests TCCore)

set_target_properties(
	CoreTests PROPERTIES FOLDER Tests
)

ADD_TEST(NAME TestCoreTests COMMAND $<TARGET_FILE:CoreTests>)
