cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(tn_log)

find_package(Boost COMPONENTS "filesystem" REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(src)

if (WITH_tn_log_EXAMPLE)
    add_subdirectory(example)
endif ()

install(EXPORT "tn-log-config" NAMESPACE tn:: DESTINATION "share/tn-log")
