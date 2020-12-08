# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

get_filename_component(project ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${project})

# Include sub-projects.
add_subdirectory (${project})
