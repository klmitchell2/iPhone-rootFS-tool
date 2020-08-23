cmake_minimum_required(VERSION 3.16)
project(iPhone_rootFS_tool C)

set(CMAKE_C_STANDARD 99)

add_executable(iPhone_rootFS_tool main.c iLibX.c iLibX.h)