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

#Libs linked to the executable
target_link_libraries(${exec_name}   
	${GLFW}
    ${VULKAN}
	imgui
)