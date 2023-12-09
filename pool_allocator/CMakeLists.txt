cmake_minimum_required(VERSION 3.2)

project(pool_allocator)

add_library(pool_allocator pool_allocator.h)

set_target_properties(pool_allocator PROPERTIES LINKER_LANGUAGE CXX)