SET(CMAKE_LIBRARY_PATH ${TAKECONTROL_DEP_DIR})

#----------------------------------------------------
# Qt
#----------------------------------------------------

IF(UNIX AND NOT ANDROID)
	SET(ENV{Qt5_DIR} "")
ENDIF()

SET(QT_WEBENGINE_VERSION 5.6.0)

# Test for supported Qt version
find_program(QMAKE_EXECUTABLE NAMES qmake HINTS $ENV{Qt5_DIR} ENV QTDIR PATH_SUFFIXES bin)
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)

SET(QT_SEARCH_MODULES "")

IF(QT_VERSION LESS QT_WEBENGINE_VERSION)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Concurrent)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Core)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Gui)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} LinguistTools)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Network)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Svg)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Widgets)
ELSE()
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Concurrent)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Core)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Gui)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} LinguistTools)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Network)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Svg)
	SET(QT_SEARCH_MODULES ${QT_SEARCH_MODULES} Widgets)
ENDIF()

FIND_PACKAGE(Qt5 REQUIRED ${QT_SEARCH_MODULES} HINTS $ENV{Qt5_DIR})

IF(QT_VERSION LESS QT_WEBENGINE_VERSION)
	INCLUDE_DIRECTORIES(${Qt5Concurrent_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Concurrent_LIBRARIES})
	INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Core_LIBRARIES})
	INCLUDE_DIRECTORIES(${Qt5Gui_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Gui_LIBRARIES})
	INCLUDE_DIRECTORIES(${Qt5Network_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Network_LIBRARIES})
	INCLUDE_DIRECTORIES(${Qt5Svg_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Svg_LIBRARIES})
	INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Widgets_LIBRARIES})
ELSE()
	INCLUDE_DIRECTORIES(${Qt5Concurrent_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Concurrent_LIBRARIES})
	INCLUDE_DIRECTORIES(SYSTEM ${Qt5Core_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Core_LIBRARIES})
	INCLUDE_DIRECTORIES(SYSTEM ${Qt5Gui_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Gui_LIBRARIES})
	INCLUDE_DIRECTORIES(SYSTEM ${Qt5Network_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Network_LIBRARIES})
	INCLUDE_DIRECTORIES(${Qt5Svg_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Svg_LIBRARIES})
	INCLUDE_DIRECTORIES(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
	SET(QT_LIBRARIES ${QT_LIBRARIES} ${Qt5Widgets_LIBRARIES})
ENDIF()
