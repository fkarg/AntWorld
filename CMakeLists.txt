cmake_minimum_required(VERSION 2.8.4)
project(AntWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES AntWorld/main.cpp)
add_executable(AntWorld ${SOURCE_FILES})



 # Define sources and executable
set(EXECUTABLE_NAME "MySFML")
add_executable(${EXECUTABLE_NAME} AntWorld/main.cpp)


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()