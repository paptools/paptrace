# Copyright (c) 2023-present, Ian Dinwoodie.
# Distributed under the MIT License (http://opensource.org/licenses/MIT).

cmake_minimum_required(VERSION 3.24)

################################################################################
# CMake policies.

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0135 NEW)

################################################################################
# Project settings.

project(paptrace VERSION 0.1.0 LANGUAGES CXX C)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Choose Release or Debug" FORCE)
endif ()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Use standardized build/install paths.
include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

################################################################################
# Options.

option(PAPTRACE_INSTALL "Generate the install targets." ON)

################################################################################
# Compiler settings.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# add_definitions(-Wall -Wextra -Werror)

################################################################################
# Third party libraries.

if (PAPTRACE_INSTALL)
  # Declared here for use by fetched dependencies.
  set(install_targets "")
endif ()

include("cmake/FindGoogleTest.cmake")
include("cmake/FindJson.cmake")

################################################################################
# Path trace library.

add_library(paptrace STATIC
  "src/paptrace.cpp"
)

target_include_directories(paptrace
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  INTERFACE
    $<INSTALL_INTERFACE:include>
)

set(paptrace_public_headers
  "include/paptrace/paptrace.h"
  "include/paptrace/utils.h"
)

set_target_properties(paptrace
  PROPERTIES
    PUBLIC_HEADER "${paptrace_public_headers}"
)

target_link_libraries(paptrace
  PUBLIC
    nlohmann_json::nlohmann_json
    GTest::gtest
)

################################################################################
# Install rules.

if (PAPTRACE_INSTALL)
  set(targets_export_name "${PROJECT_NAME}-targets")
  list(APPEND install_targets paptrace nlohmann_json)
  install(TARGETS ${install_targets}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
  )

  set(project_cmake_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "")
  export(TARGETS ${install_targets}
    NAMESPACE "${PROJECT_NAME}::"
    FILE "${PROJECT_BINARY_DIR}/${targets_export_name}.cmake"
  )
  install(EXPORT "${targets_export_name}"
    FILE "${targets_export_name}.cmake"
    NAMESPACE "${PROJECT_NAME}::"
    DESTINATION "${project_cmake_dir}"
  )

  include(CMakePackageConfigHelpers)
  set(project_config "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
  configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${project_cmake_dir}"
  )
  set(version_config "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
  write_basic_package_version_file(
    "${version_config}"
    VERSION "${paptrace_VERSION}"
    COMPATIBILITY AnyNewerVersion
  )
  install(FILES "${project_config}" "${version_config}"
    DESTINATION "${project_cmake_dir}"
  )
endif ()

################################################################################
