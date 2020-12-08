# CMakeList.txt : CMake project for SampleCMakeProject, include source and define
# project specific logic here.

# Name the project after the current source directory.
get_filename_component(project ${CMAKE_CURRENT_SOURCE_DIR} NAME)

cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${project} "${project}.cpp" "${project}.h" "test/tests-main.cpp" "${project}_test.cpp")

set_target_properties(${project} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
)

# This was required because when the program runs the data file needs to be in the 
# executable build folder.
add_custom_command(
        TARGET ${project} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/PasswordPolicy.txt
                ${CMAKE_CURRENT_BINARY_DIR}/PasswordPolicy.txt)

# Ensure that the tests run on all builds.
add_custom_target(test_${project} ALL DEPENDS ${project} COMMAND ${project})
