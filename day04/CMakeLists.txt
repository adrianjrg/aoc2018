cmake_minimum_required(VERSION 3.4)
project(day04 LANGUAGES CXX)

add_executable(day04 src/main)
set_target_properties(day04 PROPERTIES
            CXX_STANDARD 14
            )

configure_file(input.txt input04.txt COPYONLY)
