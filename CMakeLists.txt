cmake_minimum_required( VERSION "3.2.0" )

project( url_test CXX C )

include_directories( src )

add_executable( url_test src/main.cc )
