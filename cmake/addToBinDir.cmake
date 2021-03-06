IF(WIN32)
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Debug")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Debug/plugins")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Debug/plugins/iconengines")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Debug/plugins/platforms")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Release")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Release/plugins")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Release/plugins/iconengines")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Release/plugins/platforms")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/icudt54.dll" "${CMAKE_BINARY_DIR}/bin/Debug/icudt54.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/icudt54.dll" "${CMAKE_BINARY_DIR}/bin/Release/icudt54.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/icuin54.dll" "${CMAKE_BINARY_DIR}/bin/Debug/icuin54.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/icuin54.dll" "${CMAKE_BINARY_DIR}/bin/Release/icuin54.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/icuuc54.dll" "${CMAKE_BINARY_DIR}/bin/Debug/icuuc54.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/icuuc54.dll" "${CMAKE_BINARY_DIR}/bin/Release/icuuc54.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/libEGLd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/libEGLd.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/libEGL.dll" "${CMAKE_BINARY_DIR}/bin/Release/libEGL.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/libGLESv2d.dll" "${CMAKE_BINARY_DIR}/bin/Debug/libGLESv2d.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/libGLESv2.dll" "${CMAKE_BINARY_DIR}/bin/Release/libGLESv2.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/plugins/iconengines/qsvgicond.dll" "${CMAKE_BINARY_DIR}/bin/Debug/plugins/iconengines/qsvgicond.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/plugins/iconengines/qsvgicon.dll" "${CMAKE_BINARY_DIR}/bin/Release/plugins/iconengines/qsvgicon.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/plugins/platforms/qwindowsd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/plugins/platforms/qwindowsd.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/plugins/platforms/qwindows.dll" "${CMAKE_BINARY_DIR}/bin/Release/plugins/platforms/qwindows.dll")

	configure_file(${CMAKE_SOURCE_DIR}/config/qt.conf ${CMAKE_BINARY_DIR}/bin/Debug/qt.conf COPYONLY)
	configure_file(${CMAKE_SOURCE_DIR}/config/qt.conf ${CMAKE_BINARY_DIR}/bin/Release/qt.conf COPYONLY)
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Concurrentd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/Qt5Concurrentd.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Concurrent.dll" "${CMAKE_BINARY_DIR}/bin/Release/Qt5Concurrent.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Cored.dll" "${CMAKE_BINARY_DIR}/bin/Debug/Qt5Cored.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Core.dll" "${CMAKE_BINARY_DIR}/bin/Release/Qt5Core.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Guid.dll" "${CMAKE_BINARY_DIR}/bin/Debug/Qt5Guid.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Gui.dll" "${CMAKE_BINARY_DIR}/bin/Release/Qt5Gui.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Networkd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/Qt5Networkd.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Network.dll" "${CMAKE_BINARY_DIR}/bin/Release/Qt5Network.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Svgd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/Qt5Svgd.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Svg.dll" "${CMAKE_BINARY_DIR}/bin/Release/Qt5Svg.dll")
	
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Widgetsd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/Qt5Widgetsd.dll")
	LINK_TO_FILE("$ENV{Qt5_DIR}/bin/Qt5Widgets.dll" "${CMAKE_BINARY_DIR}/bin/Release/Qt5Widgets.dll")
	
	IF(WITH_TESTS)
		LINK_TO_FILE("${GTEST_DEBUG_ROOT}/bin/gtestd.dll" "${CMAKE_BINARY_DIR}/bin/Debug/gtestd.dll")
		LINK_TO_FILE("${GTEST_RELEASE_ROOT}/bin/gtest.dll" "${CMAKE_BINARY_DIR}/bin/Release/gtest.dll")
	ENDIF(WITH_TESTS)
ENDIF(WIN32)
IF(UNIX)
	file(GLOB_RECURSE files "${TAKECONTROL_DEP_DIR}/*.so*")
	foreach(filename ${files})
		get_filename_component(filename_pure ${filename} NAME)
		execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filename} ${CMAKE_BINARY_DIR}/bin/${filename_pure})
	endforeach()
ENDIF(UNIX)
