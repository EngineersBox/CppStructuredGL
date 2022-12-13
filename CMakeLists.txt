cmake_minimum_required(VERSION 3.10)

project(StructuredGL VERSION 1.0)

# Debug
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CXXFLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include source content
file (GLOB_RECURSE StructuredGL_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE StructuredGL_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (StructuredGL_INCLUDE_DIRS "")
foreach (_headerFile ${StructuredGL_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND StructuredGL_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES StructuredGL_INCLUDE_DIRS)

# Mark executable
add_executable(StructuredGL ${StructuredGL_SOURCES})
target_include_directories(StructuredGL PRIVATE ${StructuredGL_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(StructuredGL PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(StructuredGL PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(StructuredGL PUBLIC ${OPENGL_LIBRARIES})

# GLFW 3
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(StructuredGL PRIVATE glfw)

# GLAD
find_package(glad REQUIRED)
target_link_libraries(StructuredGL PRIVATE glad::glad)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(StructuredGL PRIVATE glm::glm)

# ImGui
find_package(imgui CONFIG REQUIRED)
target_link_libraries(StructuredGL PRIVATE imgui::imgui)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(StructuredGL PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
