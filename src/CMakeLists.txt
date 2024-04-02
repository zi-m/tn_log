cmake_minimum_required(VERSION 3.15)
project(tn_log_src)


install(DIRECTORY include/ DESTINATION include/tn/tn_log)


#
# tn_log
#

add_library(tn_log STATIC
        "tn_log.cpp"
)

add_library(tn::tn_log ALIAS tn_log)

target_include_directories(tn_log
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        PUBLIC "$<INSTALL_INTERFACE:include/tn/tn_log>"
)

target_link_libraries(tn_log
        PUBLIC Boost::filesystem
        PUBLIC spdlog::spdlog
)

target_compile_features(tn_log
        PUBLIC cxx_std_20
)

set_target_properties(tn_log PROPERTIES
        PREFIX ""
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE ON
)

install(TARGETS tn_log EXPORT "tn-log-config"
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
        