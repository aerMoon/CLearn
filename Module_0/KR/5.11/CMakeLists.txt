project(KR_5.11)
add_definitions(-std=c11 -Wall -O0 -gdwarf-2)
cmake_minimum_required(VERSION 2.8)
add_executable(entab entab.c)
add_executable(detab detab.c)
