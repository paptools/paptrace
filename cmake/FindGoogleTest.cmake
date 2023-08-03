# Copyright (c) 2023-present, Ian Dinwoodie.
# Distributed under the MIT License (http://opensource.org/licenses/MIT).

message(STATUS "Finding GoogleTest")

#find_package(GTest QUIET)
find_package(GTest)
if (NOT GTest_FOUND)
  message(STATUS "GoogleTest not found, fetching from source")

  include(FetchContent)
  set(gtest_version "1.12.1")
  FetchContent_Declare(gtest_content
    URL "https://github.com/google/googletest/archive/refs/tags/release-${gtest_version}.tar.gz"
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(gtest_content)

  if (PAPTRACE_INSTALL)
    list(APPEND install_targets gtest)
  endif ()
endif ()

enable_testing()
