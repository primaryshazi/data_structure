cmake_minimum_required(VERSION 3.10.0)

aux_source_directory(./ SRC_LIST)

add_executable(double_hash ${SRC_LIST})

target_link_libraries(double_hash -lm)
