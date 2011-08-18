cmake_minimum_required (VERSION 2.6)

project (libdds)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
include_directories (code)

add_definitions (-Wall -fomit-frame-pointer)

add_library (dds SHARED code/libdds.c)

add_library (dds_opengl SHARED code/libdds_opengl.c)
target_link_libraries (dds_opengl dds GL)

add_executable (Viewer viewer/main.c)
target_link_libraries (Viewer dds dds_opengl glut)
