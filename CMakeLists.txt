cmake_minimum_required (VERSION 2.6)

project (libdds)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
include_directories (code)

add_definitions (-Wall -fomit-frame-pointer)

add_library (dds SHARED code/libdds.c)

add_library (dds_opengl SHARED code/libdds_opengl.c)

add_library (dds_s STATIC code/libdds.c)
set_target_properties(dds_s PROPERTIES OUTPUT_NAME dds)

add_library (dds_opengl_s STATIC code/libdds_opengl.c)
set_target_properties(dds_opengl_s PROPERTIES OUTPUT_NAME dds_opengl)

target_link_libraries (dds_opengl dds GL)
target_link_libraries (dds_opengl_s dds GL)

add_executable (Viewer viewer/main.c)
target_link_libraries (Viewer dds dds_opengl glut)
