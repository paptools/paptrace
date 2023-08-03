# Copyright (c) 2023-present, Ian Dinwoodie.
# Distributed under the MIT License (http://opensource.org/licenses/MIT).

set(nlohmann_json_version "3.11.2")
message(STATUS "Fetching nlohmann_json ${nlohmann_json_version}")

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install ON CACHE INTERNAL "")

include(FetchContent)
FetchContent_Declare(nlohmann_json
  URL "https://github.com/nlohmann/json/archive/refs/tags/v${nlohmann_json_version}.tar.gz"
)
FetchContent_MakeAvailable(nlohmann_json)
