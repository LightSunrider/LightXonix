cmake_minimum_required(VERSION 3.8)

project(glad)

set(PRJ_DIR "${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} STATIC 
    "${PRJ_DIR}/src/glad.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PRJ_DIR}/include"
)
