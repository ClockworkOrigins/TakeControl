SET(srcdir ${CMAKE_CURRENT_SOURCE_DIR})
SET(includedir ${CMAKE_SOURCE_DIR}/include/core)

INCLUDE_DIRECTORIES(${includedir})

FILE(GLOB_RECURSE Gothic2PluginTestsSrc ${srcdir}/*.cpp)
FILE(GLOB_RECURSE Gothic2PluginTestsHeader ${includedir}/*.h)

ADD_EXECUTABLE(Gothic2PluginTests ${CMAKE_SOURCE_DIR}/src/gothic2plugin/Gothic2Plugin.cpp ${Gothic2PluginTestsSrc} ${Gothic2PluginTestsGuiHeader})

target_link_libraries(Gothic2PluginTests debug ${GTEST_DEBUG_LIBRARIES} optimized ${GTEST_RELEASE_LIBRARIES})
target_link_libraries(Gothic2PluginTests ${QT_LIBRARIES})
target_link_libraries(Gothic2PluginTests TCCore)
target_link_libraries(Gothic2PluginTests TCPlugins)
target_link_libraries(Gothic2PluginTests TCUtils)

set_target_properties(
	Gothic2PluginTests PROPERTIES FOLDER Tests
)

ADD_TEST(NAME TestGothic2PluginTests COMMAND $<TARGET_FILE:Gothic2PluginTests>)
