cmake_minimum_required(VERSION 2.8)
project(AntWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES "main.cpp")
add_executable(AntWorld ${SOURCE_FILES})

# include_directories("${PROJECT_SOURCE_DIR}/*")


 # Define sources and executable
set(EXECUTABLE_NAME "Run_AntWorld")
add_executable(${EXECUTABLE_NAME} main.cpp)



# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()



# Trying to configure cmake so that it works ...


include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}")

add_subdirectory(TGUI)

export(TARGETS TGUI FILE "${PROJECT_BINARY_DIR}/




