
find_package(cmakego REQUIRED COMPONENTS gstreamer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
#find_package(Qt5OpenGL REQUIRED)

QT5_WRAP_UI(UIS_HDRS app2view.ui)


#QT5_ADD_RESOURCES(RESOURCES MMRiskGUI.qrc)
#MACOSX_BUNDLE

set(QTDEPS 	Qt5::Core 	Qt5::Gui 	Qt5::Widgets)
set(CMAKE_AUTOMOC ON)


add_executable(MyProject app1.cpp)
target_link_libraries(MyProject ${QTDEPS} p::gstreamer)

add_executable(MyProject2 app2.cpp appview2.cpp)
target_link_libraries(MyProject2 ${QTDEPS} p::gstreamer)
