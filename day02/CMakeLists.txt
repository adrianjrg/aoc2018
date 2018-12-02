cmake_minimum_required(VERSION 3.4)
project(day02 LANGUAGES CXX)

add_executable(day02 src/main)
set_target_properties(day02 PROPERTIES
            CXX_STANDARD 14
            )

configure_file(input.txt input.txt COPYONLY)
