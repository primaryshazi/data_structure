cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(./ SRC_LIST)

add_executable(queue ${SRC_LIST})
