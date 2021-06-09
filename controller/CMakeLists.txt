cmake_minimum_required(VERSION 3.0)

project(robot)

set(sources 
    src/main.c
    src/i2c.c
    src/i2c.h
    src/tof.c
    src/tof.h
    src/drive.c
    src/drive.h
    src/map.c
    src/map.h
    src/msgq.c
    src/msgq.h
    src/server.c
    src/server.h
)

find_package(PkgConfig)

pkg_check_modules(PROTOBUF protobuf REQUIRED)

set(flags
    -g
    -pg
    -Wall
)

find_library(PIGPIO_LIB pigpio /usr/lib)
find_path(PIGPIO_INCL pigpio.h /usr/include) 

set(incl
    ${PROTOBUF_INCLUDE_DIRS}
    ${PIGPIO_INCL}
)

set(libs
    ${PROTOBUF_LIBRARIES}
    ${PIGPIO_LIB}
    rt
    pthread
)

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE ${flags})
target_include_directories(${PROJECT_NAME} PRIVATE ${incl})
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})
