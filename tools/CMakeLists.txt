cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tools)

set(sources
    cryptor.cc
)

add_executable(cryptor ${sources})

target_include_directories(cryptor PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${PROJECT_INCLUDE_DIR}/encrypt
)

target_link_libraries(cryptor PRIVATE
    encrypt::encrypt
    cryptopp::cryptopp
    gflags::gflags
)

install(TARGETS cryptor DESTINATION bin)
