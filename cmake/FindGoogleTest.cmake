# Copyright (c) 2023-present, Ian Dinwoodie.
# Distributed under the MIT License (http://opensource.org/licenses/MIT).

set(gtest_version "1.12.1")
message(STATUS "Fetching GoogleTest ${test_version}")

include(FetchContent)

FetchContent_Declare(gtest
  URL "https://github.com/google/googletest/archive/refs/tags/release-${gtest_version}.tar.gz"
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

enable_testing()
