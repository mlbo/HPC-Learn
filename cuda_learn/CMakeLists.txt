cmake_minimum_required(VERSION 3.16)
project(CUDA CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_executable(CUDA main.cu)

set_target_properties(
        CUDA
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)