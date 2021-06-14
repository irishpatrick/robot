cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(sensors)

add_subdirectory(./pico-servo)

# Initialize the SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
	src/blink.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include ${CMAKE_SOURCE_DIR}/pico-servo/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/pico-servo)
target_link_libraries(${PROJECT_NAME} pico-servo pico_stdlib hardware_pwm)

pico_add_extra_outputs(${PROJECT_NAME})
