cmake_minimum_required(VERSION 3.10)

project(encrypt VERSION 1.0.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(public_headers
    crypto.hpp
)

set(private_headers
    crypto_impl.hpp
)

set(sources
    crypto.cpp
    crypto_impl.cpp
)

add_library(encrypt SHARED
    ${sources}
    ${public_headers}
    ${private_headers}
)
add_library(encrypt::encrypt ALIAS encrypt)

target_include_directories(encrypt
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/encrypt>
    PRIVATE
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(encrypt PRIVATE
    cryptopp::cryptopp
)

install(TARGETS encrypt
    EXPORT encrypt_export_set
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
)

install(FILES ${public_headers}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/encrypt
    COMPONENT dev
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

export(EXPORT encrypt_export_set
    FILE "${CMAKE_CURRENT_BINARY_DIR}/encrypt-targets.cmake"
    NAMESPACE encrypt::
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/encrypt-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_DATADIR}/encrypt
    COMPONENT dev
)

install(EXPORT encrypt_export_set
    FILE encrypt-targets.cmake
    NAMESPACE encrypt::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/encrypt
    COMPONENT dev
)
