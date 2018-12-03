cmake_minimum_required(VERSION 3.4)
project(day01 LANGUAGES CXX)

add_executable(day01 src/main)
set_target_properties(day01 PROPERTIES
            CXX_STANDARD 14
            )

configure_file(input.txt input01.txt COPYONLY)
