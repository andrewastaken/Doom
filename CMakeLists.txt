cmake_minimum_required(VERSION 3.13.0)

project(${CMAKE_PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(OpenGL REQUIRED)

add_subdirectory(thirdparty/glfw-3.4)
add_subdirectory(thirdparty/glm)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES src/*.h)

add_executable(Raycaster ${SRC_FILES} ${HEADER_FILES} thirdparty/glad/src/glad.c)

target_include_directories(Raycaster PRIVATE ${OPENGL_INCLUDE_DIRS} thirdparty/glad/include/)
target_link_libraries(Raycaster PRIVATE ${OPENGL_LIBRARIES} glfw glm::glm)
