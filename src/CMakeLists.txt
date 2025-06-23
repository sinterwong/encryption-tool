CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(encrypt VERSION 1.0.0) # Added version

INCLUDE(GNUInstallDirs) # For standard installation directories
INCLUDE(CMakePackageConfigHelpers) # For generating config files

SET(CMAKE_POSITION_INDEPENDENT_CODE ON) 

# No longer need DEPENDENCY_INCLUDES as it will be handled by target_include_directories

SET(DEPENDENCY_LIBS
	cryptopp::cryptopp
)

FILE(GLOB CURRENT_DIR_PUBLIC_HEAD RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} crypto.hpp) # Public headers
FILE(GLOB CURRENT_DIR_PRIVATE_HEAD RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} crypto_impl.hpp) # Private headers
FILE(GLOB CURRENT_DIR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} crypto.cpp crypto_impl.cpp)

# No longer need to manually copy headers

ADD_LIBRARY(encrypt SHARED
    ${CURRENT_DIR_SRCS}
    ${CURRENT_DIR_PUBLIC_HEAD}
    ${CURRENT_DIR_PRIVATE_HEAD}
)
ADD_LIBRARY(encrypt::encrypt ALIAS encrypt) # Alias for modern CMake usage

TARGET_INCLUDE_DIRECTORIES(encrypt
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> # For build tree
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/encrypt> # For install tree, headers will be in 'encrypt' subdir
    PRIVATE
        ${PROJECT_INCLUDE_DIR} # If there are any truly private internal includes from root
)
TARGET_LINK_LIBRARIES(encrypt PRIVATE ${DEPENDENCY_LIBS})

# Install the target and its public headers
INSTALL(TARGETS encrypt
    EXPORT encrypt_export_set
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
    # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/encrypt COMPONENT dev # Alternative way to install public headers
)

# Install the public header files explicitly for the package
INSTALL(FILES ${CURRENT_DIR_PUBLIC_HEAD}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/encrypt # Keep them in an 'encrypt' subdirectory for namespacing
    COMPONENT dev
)

# Generate the encrypt-config.cmake and encrypt-config-version.cmake files
WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

EXPORT(EXPORT encrypt_export_set
    FILE "${CMAKE_CURRENT_BINARY_DIR}/encrypt-targets.cmake"
    NAMESPACE encrypt::
)

CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/encrypt-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config.cmake"
    @ONLY
)

INSTALL(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/encrypt-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_DATADIR}/encrypt
    COMPONENT dev
)

INSTALL(EXPORT encrypt_export_set
    FILE encrypt-targets.cmake
    NAMESPACE encrypt::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/encrypt
    COMPONENT dev
)
