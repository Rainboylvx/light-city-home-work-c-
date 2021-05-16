# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目名称
project(String)

# 指定编译flag
set(CMAKE_CXX_FLAGS "-std=c++17 -g")

# 设置宏
add_definitions(-D DEBUG)

# 指定include 的头文件的位置
#include_directories(src/include)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

add_executable(test ${DIR_SRCS})
