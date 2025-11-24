cmake_minimum_required(VERSION 3.10)

project(EncryptionTool VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_ENCRYPTION_TOOL_TESTS "Build with tests" OFF)
option(BUILD_ENCRYPTION_TOOLS "Build with tools" OFF)

include(GNUInstallDirs)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose Release, Debug, RelWithDebInfo or MinSizeRel" FORCE)
endif()

set(output_root ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_root}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${output_root}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${output_root}/lib)
set(PROJECT_INCLUDE_DIR ${output_root}/include)

message(STATUS "--------------------------------")
message(STATUS "Build EncryptionTool: ${PROJECT_VERSION}")
message(STATUS "Build with tests: ${BUILD_ENCRYPTION_TOOL_TESTS}")
message(STATUS "Build with tools: ${BUILD_ENCRYPTION_TOOLS}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CXX standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
endif()
message(STATUS "--------------------------------")

add_subdirectory(3rdparty)
add_subdirectory(src)

if(BUILD_ENCRYPTION_TOOL_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_ENCRYPTION_TOOLS)
    add_subdirectory(tools)
endif()
