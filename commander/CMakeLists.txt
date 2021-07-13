cmake_minimum_required(VERSION 3.0)

project(commander)

set(sources
    src/client.c
    src/client.h
    src/display.c
    src/display.h
    src/input.c
    src/input.h
    src/main.c
    src/packet.c
    src/packet.h
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

set(flags -pthread)

set(incl
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}    
)

set(libs
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    -pthread
)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})
target_include_directories(${PROJECT_NAME} PRIVATE ${incl})
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})
