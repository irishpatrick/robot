cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(sensors)

# Initialize the SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
	src/blink.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pwm)

