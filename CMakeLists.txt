cmake_minimum_required( VERSION "3.2.0" )

project( url_test CXX C )

include_directories( src )

set( URL_TEST_COMPILE_OPTIONS
    -Wall
    -Wextra
    -O3
    -std=c++17
)

add_executable( url_test src/main_test.cc src/Url.cc )
set_target_properties( url_test
    PROPERTIES
    COMPILE_OPTIONS          "${URL_TEST_COMPILE_OPTIONS}"
)




set( URL_PROFILE_COMPILE_OPTIONS
    -Wall
    -Wextra
    -O3
    -std=c++17
    -g
    -pg
)

add_executable( url_profile src/main_profile.cc src/Url.cc )
set_target_properties( url_profile
    PROPERTIES
    COMPILE_OPTIONS          "${URL_PROFILE_COMPILE_OPTIONS}"
)