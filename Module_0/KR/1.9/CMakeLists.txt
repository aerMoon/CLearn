project(KR_1.9)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(app ${SRC_LIST})
