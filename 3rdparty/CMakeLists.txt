CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(EncryptionTool3rdparty)

SET(BUILD_TESTING OFF CACHE BOOL "Disable testing for 3rdparty libs")
SET(WITH_GTEST OFF CACHE BOOL "Disable gtest")

IF(NOT TARGET gtest)
  MESSAGE(STATUS "gtest target not found. Adding subdirectory...")
  ADD_SUBDIRECTORY(googletest EXCLUDE_FROM_ALL)
ELSE()
  MESSAGE(STATUS "gtest target already exists. Skipping.")
ENDIF()

IF(NOT TARGET gflags)
  MESSAGE(STATUS "gflags target not found. Adding subdirectory...")
  ADD_SUBDIRECTORY(gflags EXCLUDE_FROM_ALL)
ELSE()
  MESSAGE(STATUS "gflags target already exists. Skipping.")
ENDIF()

IF(NOT TARGET cryptopp)
  MESSAGE(STATUS "cryptopp target not found. Adding subdirectory...")
  SET(CRYPTOPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp)
  
  # 禁用 cryptopp 的测试和文档构建
  SET(CRYPTOPP_BUILD_TESTING OFF CACHE BOOL "Disable cryptopp tests" FORCE)
  SET(CRYPTOPP_BUILD_DOCUMENTATION OFF CACHE BOOL "Disable cryptopp docs" FORCE)
  
  # 只在构建静态库时才安装 cryptopp
  if(NOT BUILD_SHARED_LIBS)
    MESSAGE(STATUS "Building static library - cryptopp will be installed")
    SET(CRYPTOPP_INSTALL ON CACHE BOOL "Install cryptopp" FORCE)
  else()
    MESSAGE(STATUS "Building shared library - cryptopp will NOT be installed")
    SET(CRYPTOPP_INSTALL OFF CACHE BOOL "Do not install cryptopp" FORCE)
  endif()
  
  ADD_SUBDIRECTORY(cryptopp-cmake)
  
  # 排除测试目标
  if(TARGET cryptest)
    set_target_properties(cryptest PROPERTIES EXCLUDE_FROM_ALL TRUE)
  endif()
  
  # 不再手动添加 install 规则，让 cryptopp-cmake 自己处理
ELSE()
  MESSAGE(STATUS "cryptopp target already exists. Skipping.")
ENDIF()