
cmake_minimum_required(VERSION 3.20)

set(project_name "Phantom")
project(${project_name})

# set cmake folder
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


# Set the C/C++ specified in the projects as requirements
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)


set(ROOT_DIR "external")

#####################################################################################
# Vulkan
#
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})
set(VULKAN ${Vulkan_LIBRARIES})

#####################################################################################
# GLFW
#use the FindGLFW.cmake in cmake folder
Message(STATUS "--> using package GLFW")
set(EXTERNAL "external")
set(GLFW_ROOT_DIR ${EXTERNAL})
set(GLFW_USE_STATIC_LIBS ON)
find_package(GLFW REQUIRED)

include_directories(${GLFW_INCLUDE_DIR})
set(GLFW ${GLFW_LIBRARY})

#####################################################################################
# GLM
#use the FindGLM.cmake in cmake folder
Message(STATUS "--> using package GLM")
set(GLM_ROOT_DIR "external")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

#####################################################################################
# ImGUI
#
# add windows, linux and mac specific files
# use glfw as backend
file(GLOB IMGUI_BACKEND_SOURCES
    ${ROOT_DIR}/include/imgui/backends/imgui_impl_glfw.*
    ${ROOT_DIR}/include/imgui/backends/imgui_impl_vulkan.*
    ${ROOT_DIR}/include/imgui/backends/imgui_impl_win32.*
)

Message(STATUS "--> using package ImGUI")
# Manually add imgui
add_library(imgui STATIC
    ${ROOT_DIR}/include/imgui/imgui.cpp
    ${ROOT_DIR}/include/imgui/imgui_draw.cpp
    ${ROOT_DIR}/include/imgui/imgui_widgets.cpp
    ${ROOT_DIR}/include/imgui/imgui_demo.cpp
    ${ROOT_DIR}/include/imgui/imgui_tables.cpp
)

target_sources(imgui 
    PRIVATE
        ${IMGUI_BACKEND_SOURCES}
)

target_include_directories(imgui
    PUBLIC
        ${ROOT_DIR}/include/imgui
        ${ROOT_DIR}/include/imgui/backends
)

target_link_libraries(imgui
     PRIVATE
         ${GLFW}
)

#####################################################################################
# STB
#
Message(STATUS "--> using package stb")
include_directories(${ROOT_DIR}/include/stb)

#####################################################################################
# TINYOBJ
#
Message(STATUS "--> using package OBJ")
include_directories(${ROOT_DIR}/include/tinyobjloader)

#####################################################################################
# TINYGLTF
#
Message(STATUS "--> using package GLTF")
include_directories(${ROOT_DIR}/include/tinygltf)

#####################################################################################
# Expected
#
Message(STATUS "--> using package Expected")
include_directories(${ROOT_DIR}/include/expected/include/tl)

#####################################################################################
# ShaderC
#
find_library(SHADERC_LIB shaderc_combined $ENV{VULKAN_SDK}/Lib)
MESSAGE(STATUS "Found shaderc in: ${SHADERC_LIB}")

#####################################################################################
# VMA
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

# add subprojects
add_subdirectory(Core)
add_subdirectory(PathTracer)
add_subdirectory(Editor)

# target_link_libraries(${CMAKE_PROJECT_NAME}
#     ${LIBRARIES}
#     ${VULKANLIB}
# )


# set editor as the start-up project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor)