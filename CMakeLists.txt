cmake_minimum_required(VERSION 3.13.0)

project(${CMAKE_PROJECT_NAME})

set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(OpenGL REQUIRED)

add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/glm)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} thirdparty/glad/src/glad.c)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS} thirdparty/glad/include/)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} glfw glm::glm)
