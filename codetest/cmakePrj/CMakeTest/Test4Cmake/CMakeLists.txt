cmake_minimum_required(VERSION 3.10)

# Set the project name
project(test4cmake)

aux_source_directory(. DIR_SRCS)
message(STATUS "${DIR_SRCS}")

# Add the executable
add_executable(test4cmake ${DIR_SRCS})

