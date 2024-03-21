Message(STATUS "--> making Editor executable")

#CMake minimum requirement 
cmake_minimum_required(VERSION 3.20)

set(exec_name "Editor")

#GLOB source files 
file(GLOB_RECURSE src_files 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.*
	${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.*
)

#Executable
add_executable(${exec_name} ${src_files})

# Include directories for Editor
target_include_directories(${exec_name} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_compile_definitions(${exec_name} PRIVATE)

#Libs linked to the executable
# Also linking Core library to Editor
target_link_libraries(${exec_name}   
	Core
    ${GLFW}
    ${VULKAN}
	imgui
${SHADERC_LIB}
VulkanMemoryAllocator
spdlog::spdlog_header_only
)


set_target_properties(${exec_name} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Editor/src"
)
