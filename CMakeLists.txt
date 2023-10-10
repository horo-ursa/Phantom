
cmake_minimum_required(VERSION 3.20)

set(project_name "Phantom")
project(${project_name})

# set cmake folder
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


# Set the C/C++ specified in the projects as requirements
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(Vulkan REQUIRED)

#####################################################################################
# GLFW
#use the FindGLFW.cmake in cmake folder
Message(STATUS "--> using package GLFW")
set(EXTERNAL "external")
set(GLFW_ROOT_DIR ${EXTERNAL})
set(GLFW_USE_STATIC_LIBS ON)
find_package(GLFW REQUIRED)

include_directories(${GLFW_INCLUDE_DIR})
set(LIBRARIES ${GLFW_LIBRARY})

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
Message(STATUS "--> using package ImGUI")
set(IMGUI_ROOT_DIR "external")
include_directories(${IMGUI_ROOT_DIR}/include/imgui)


find_package(ImGui REQUIRED)
find_package(tinyobjloader REQUIRED)