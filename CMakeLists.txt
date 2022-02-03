cmake_minimum_required(VERSION 3.19)
project(IslandGame)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles")
find_package(SFML REQUIRED system window graphics network audio)
FIND_PACKAGE(TinyXML2 REQUIRED)
FIND_PACKAGE(TinyXML REQUIRED)
include_directories(${SFML_INCLUDE_DIR} ${TinyXML2_INCLUDE_DIR} ${TinyXML_INCLUDE_DIR})
include_directories(Client/includeClient)
include_directories(Server/includeServer)
include_directories(EventBus/Include)

add_executable(Client Client/srcClient/main.cpp Client/srcClient/ShipResourceText.cpp EventBus/EventBus.cpp
Client/includeClient/view.h Client/includeClient/map.h Client/includeClient/camera.h Client/includeClient/Lev.h
        Client/includeClient/resources.h Client/srcClient/Lev.cpp Client/srcClient/WinText.cpp Client/includeClient/Maze.h)
add_executable(Server Server/srcServer/main.cpp EventBus/EventBus.cpp Server/srcServer/Player.cpp Server/srcServer/Collision.cpp Client/srcClient/Lev.cpp)

target_link_libraries(Client ${SFML_LIBRARIES} ${TinyXML2_LIBRARIES} ${TinyXML2_DEPENDENCIES} ${TinyXML_LIBRARIES} ${TinyXML_DEPENDENCIES})
target_link_libraries(Server ${SFML_LIBRARIES} ${TinyXML2_LIBRARIES} ${TinyXML2_DEPENDENCIES} ${TinyXML_LIBRARIES} ${TinyXML_DEPENDENCIES})
