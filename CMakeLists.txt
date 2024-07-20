cmake_minimum_required(VERSION 3.28)
project(PlotZone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DTANGRAM_WINDOWS)
add_subdirectory(3rdparty)

find_package(PkgConfig REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GDAL CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

pkg_check_modules(LIBSPATIALITE REQUIRED spatialite)
pkg_check_modules(FONTCONFIG REQUIRED Fontconfig)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(
        UI_HEADERS
        ${INCLUDE_DIR}/Application.h
        ${INCLUDE_DIR}/State/ApplicationState.h

        ${INCLUDE_DIR}/Service/Service.h
        ${INCLUDE_DIR}/Service/DataTableService.h
        ${INCLUDE_DIR}/Service/DataManagerService.h

        ${INCLUDE_DIR}/UI/UI.h
        ${INCLUDE_DIR}/UI/DataTable/DataTable.h
        ${INCLUDE_DIR}/UI/DataTable/DataTableMenu.h
        ${INCLUDE_DIR}/UI/DataTable/DataTableWindow.h
        ${INCLUDE_DIR}/UI/DataTable/DataTableQuery.h
        ${INCLUDE_DIR}/UI/DataTable/DataTableFilter.h

        ${INCLUDE_DIR}/UI/Map/MapWindow.h
        ${INCLUDE_DIR}/UI/Map/MapRenderer.h
        ${INCLUDE_DIR}/UI/Map/MapController.h

        ${INCLUDE_DIR}/UI/MainMenu/MenuBar.h
        ${INCLUDE_DIR}/UI/MainMenu/FileMenu.h
        ${INCLUDE_DIR}/UI/MainMenu/EditMenu.h

        ${INCLUDE_DIR}/Actor/Actor.h
        ${INCLUDE_DIR}/Actor/Message.h
        ${INCLUDE_DIR}/Actor/IMessage.h

        ${INCLUDE_DIR}/Utils/Utils.h
        ${INCLUDE_DIR}/Utils/Types.h
        ${INCLUDE_DIR}/Utils/Thread.h
        ${INCLUDE_DIR}/Utils/ServiceLocator.h
        ${INCLUDE_DIR}/Utils/Icons.h

        ${INCLUDE_DIR}/Renderer/Renderer.h
        ${INCLUDE_DIR}/Renderer/UrlClient.h
        ${INCLUDE_DIR}/Renderer/SystemFontHelper.h
        ${INCLUDE_DIR}/Renderer/PlatformGl.h
        ${INCLUDE_DIR}/Renderer/FrameBufferObject.h

        ${INCLUDE_DIR}/State/DataTableWindowState.h
        ${INCLUDE_DIR}/State/MapWindowState.h

        ${INCLUDE_DIR}/UI/PopupModal/PopupModal.h
)
set(
        UI_SOURCES
        ${CMAKE_SOURCE_DIR}/src/Application.cpp

        ${CMAKE_SOURCE_DIR}/src/Service/DataTable/DataTableQuery.h
        ${CMAKE_SOURCE_DIR}/src/Service/DataTable/DataTableImpl.h
        ${CMAKE_SOURCE_DIR}/src/Service/DataTable/DataTableService.cpp
        ${CMAKE_SOURCE_DIR}/src/Service/DataManager/DataManagerImpl.h
        ${CMAKE_SOURCE_DIR}/src/Service/DataManager/DataManagerService.cpp

        ${CMAKE_SOURCE_DIR}/src/UI/DataTable/DataTable.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/DataTable/DataTableMenu.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/DataTable/DataTableWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/DataTable/DataTableQuery.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/DataTable/DataTableFilter.cpp

        ${CMAKE_SOURCE_DIR}/src/UI/Map/MapWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/Map/MapRenderer.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/Map/MapController.cpp

        ${CMAKE_SOURCE_DIR}/src/Renderer/Renderer.cpp
        ${CMAKE_SOURCE_DIR}/src/Renderer/UrlClient.cpp
        ${CMAKE_SOURCE_DIR}/src/Renderer/SystemFontHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/Renderer/PlatformGl.cpp

        ${CMAKE_SOURCE_DIR}/src/UI/MainMenu/MenuBar.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/MainMenu/FileMenu.cpp
        ${CMAKE_SOURCE_DIR}/src/UI/MainMenu/EditMenu.cpp

        ${CMAKE_SOURCE_DIR}/src/UI/PopupModal/PopupModal.cpp
)

add_executable(
        PlotZone ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${UI_SOURCES}
        ${UI_HEADERS}
)

target_include_directories(PlotZone PUBLIC ${LIBSPATIALITE_INCLUDE_DIRS} ${FONTCONFIG_INCLUDE_DIRS})
target_link_directories(PlotZone PUBLIC ${LIBSPATIALITE_LIBRARY_DIRS} ${FONTCONFIG_LIBRARY_DIRS})
target_link_libraries(PlotZone PRIVATE ${LIBSPATIALITE_LIBRARIES} ${FONTCONFIG_LIBRARIES})

target_include_directories(PlotZone PUBLIC ${INCLUDE_DIR})
target_link_libraries(PlotZone PRIVATE imgui::imgui glfw OpenGL::GL GDAL::GDAL)
target_link_libraries(PlotZone PRIVATE tangram-core ws2_32 CURL::libcurl glad::glad glm::glm)
