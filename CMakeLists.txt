cmake_minimum_required(VERSION 3.10)

project(CloudSeedCore VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(DSP)

add_executable(CloudSeedDemo
    PluginProcessor.cpp
)

set(CLOUDSEED_MAX_BUFFER_SIZE 1024 CACHE STRING "Maximum allocated and supported buffer size for CloudSeedCore")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h
)

include_directories(PRIVATE CLoudSeedCore
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(CloudSeedDemo PUBLIC
    MAX_STR_SIZE=32
)

if(WIN32)
    target_compile_definitions(CloudSeedCore PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

target_link_libraries(CloudSeedDemo PRIVATE CloudSeedCore)
