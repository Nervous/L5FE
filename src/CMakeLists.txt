cmake_minimum_required(VERSION 2.8)

project(42sh)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99 -pedantic")

# defines the files to compile, just add the files you want to include
#in the compilation
file(
    GLOB_RECURSE
    source_files
    main.c
)

#executable will be named 42sh in put in build/
#and will be compiled with files listed in source_files
add_executable(
    42sh
    ${source_files}
)
