
cmake_minimum_required(VERSION 3.4)

#set the path to "cmake" folder in llvm build
#set(ENV{LLVM_DIR} "/Users/dchen/tools/llvm-7.0.1/build/lib/cmake")
set(ENV{LLVM_DIR} "/Users/dchen/tools/llvm-8.0.0/build/lib/cmake")

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(src)
