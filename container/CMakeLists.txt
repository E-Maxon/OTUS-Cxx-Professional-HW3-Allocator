cmake_minimum_required(VERSION 3.2)

project(container)

add_library(container container.h)

set_target_properties(container PROPERTIES LINKER_LANGUAGE CXX)