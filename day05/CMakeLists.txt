cmake_minimum_required(VERSION 3.4)
project(day05 LANGUAGES CXX)

add_executable(day05 src/main)
set_target_properties(day05 PROPERTIES
            CXX_STANDARD 14
            )

configure_file(input.txt input05.txt COPYONLY)
