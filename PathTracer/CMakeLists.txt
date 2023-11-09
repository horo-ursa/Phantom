Message(STATUS "--> making PathTracer executable")
#CMake minimum requirement 
cmake_minimum_required(VERSION 3.20)

set(exec_name "PathTracer")

#GLOB source files 
file(GLOB_RECURSE src_files 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.*
	${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.*
)

#Executable
add_executable(${exec_name} ${src_files})

#include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

#Libs linked to the executable
target_link_libraries(${exec_name}   
	${GLFW}
	${VULKAN}
	imgui
	${SHADERC_LIB}
VulkanMemoryAllocator
)


set_target_properties(${exec_name} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/PathTracer/src"
)
