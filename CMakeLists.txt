cmake_minimum_required(VERSION 3.5)

project(MusicPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MusicPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        TitleBar.h TitleBar.cpp
        SelectBar.h SelectBar.cpp
        src.qrc
        CentralWidget.h CentralWidget.cpp
        PlayerBar.h PlayerBar.cpp
        MainWidget.h MainWidget.cpp
        ImageLabel.h ImageLabel.cpp
        ProgressBar.h ProgressBar.cpp


        PlayList.h PlayList.cpp
        AnimationButton.h AnimationButton.cpp
        PlayListContentView.h PlayListContentView.cpp
        PlayListView.h PlayListView.cpp
        PlayListItem.h PlayListItem.cpp




        Service/DataBaseService.h


        Service/PlayListService.h Service/PlayListService.cpp
        Service/BaseService.h Service/BaseService.cpp

        Service/PlayerController.h Service/PlayerController.cpp
        UI/SidePlayListBar.h UI/SidePlayListBar.cpp
        UI/SidePlayList.h UI/SidePlayList.cpp
        UI/ClickedEventFilter.h
        UI/SidePlayListItem.h UI/SidePlayListItem.cpp
        Service/PlayListItemService.h Service/PlayListItemService.cpp
        Dtos/BaseDto.h
        Dtos/MusicDto.h
        Dtos/PlayListDto.h
        Service/DataBaseService.cpp
        Service/MusicService.h Service/MusicService.cpp
        Dtos/PlayListItemDto.h Dtos/PlayListItemDto.cpp
        UI/IndexWidget.h UI/IndexWidget.cpp
        UI/MoreMenu.h UI/MoreMenu.cpp
        UI/ToolButton.h UI/ToolButton.cpp
        UI/IndexPlayListItem.h UI/IndexPlayListItem.cpp
        UI/PlayListEditor.h UI/PlayListEditor.cpp
        Service/PlayingListManager.h Service/PlayingListManager.cpp
        Dtos/UserDto.h
        Service/UserService.h Service/UserService.cpp





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MusicPlayer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MusicPlayer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MusicPlayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(TAG_LIB_DIR D:/code/Qt/learning/MusicPlayer/lib/taglib)
# set (TAG_LIB_DIR "C:/Program Files (x86)/taglib")

include_directories(${TAG_LIB_DIR}/include)
# link_directories(${TAG_LIB_DIR}/lib)
# link_libraries(${TAG_LIB_DIR}/lib)

target_link_libraries(MusicPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MusicPlayer PRIVATE Qt6::Sql)
target_link_libraries(MusicPlayer PRIVATE Qt6::Multimedia)

# target_include_directories(MusicPlayer PRIVATE ${TAG_LIB_DIR}/include)
target_link_libraries(MusicPlayer PRIVATE ${TAG_LIB_DIR}/lib/libtag.dll.a)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MusicPlayer)
endif()
set_target_properties(MusicPlayer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS MusicPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# install(DIRECTORY D:/DEMO/3rd/opencv-3.0/bin/Release/
# 	DESTINATION ${PROJECT_BINARY_DIR}/bin)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MusicPlayer)
endif()
