cmake_minimum_required( VERSION "3.2.0" )

project( url_test CXX C )

include_directories( src )

set( URL_TEST_COMPILE_OPTIONS
    -Wall
    -Wextra
    -O3
    -std=c++17
)

add_executable( url_test src/main.cc src/Url.cc )
set_target_properties( url_test
    PROPERTIES
    COMPILE_OPTIONS          "${URL_TEST_COMPILE_OPTIONS}"
)

