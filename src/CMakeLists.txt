cmake_minimum_required(VERSION 2.8)

project(42sh)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")

#creates a list named SRCS that contains main.c
set(SRCS struct.h main.c get_options.c get_options.h)

add_subdirectory(parser)
add_subdirectory(ast)
add_subdirectory(lexer)

# defines the files to compile, just add the files you want to include
#in the compilation
#file(
#    GLOB_RECURSE
#    source_files
#    ${SRCS}
#)
#executable will be named 42sh in put in build/
#and will be compiled with files listed in source_files
add_executable(

    42sh

    ${SRCS}

)

target_link_libraries(42sh ast)
target_link_libraries(42sh lexer)
target_link_libraries(42sh parser)
