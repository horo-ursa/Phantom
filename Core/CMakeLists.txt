Message(STATUS "--> making Core executable")

#CMake minimum requirement 
cmake_minimum_required(VERSION 3.20)

set(exec_name "Core")

#GLOB source files 
file(GLOB_RECURSE src_files 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.*
	${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.*
)

#Executable
add_library(${exec_name} STATIC ${src_files})

target_include_directories(${exec_name} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

#Libs linked to the executable
target_link_libraries(${exec_name}   
	${GLFW}
    ${VULKAN}
	imgui
${SHADERC_LIB}
)

target_link_libraries(${exec_name} PRIVATE GPUOpen::VulkanMemoryAllocator)

#set_target_properties(${exec_name} PROPERTIES
#    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Core/src"
#)
