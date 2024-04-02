cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(tn_log_example)


#
# tn_log_example_01
#

add_executable(tn_log_example_01
        "tn_log_example_01.cpp"
)

target_link_libraries(tn_log_example_01
        PRIVATE tn::tn_log
)

set_target_properties(tn_log_example_01 PROPERTIES
        PREFIX ""
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE ON
)

install(TARGETS tn_log_example_01 EXPORT "tn-process-config"
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
