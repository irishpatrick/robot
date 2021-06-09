cmake_minimum_required(VERSION 3.0)

project(robot-controller)

set(sources
    src/client.c
    src/client.h
    src/main.c
)

find_package(PkgConfig REQUIRED)

set(flags -pthread)
set(libs -pthread)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})
