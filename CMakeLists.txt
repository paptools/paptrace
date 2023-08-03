# Copyright (c) 2023-present, Ian Dinwoodie.
# Distributed under the MIT License (http://opensource.org/licenses/MIT).

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

if (PAPTOOLS_INSTALL)
  set(paptrace_install_targets paptrace gtest)
  install(TARGETS ${paptrace_install_targets}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/paptrace"
  )

  list(APPEND install_targets ${paptrace_install_targets})
  set(install_targets ${install_targets} PARENT_SCOPE)
endif ()

################################################################################
