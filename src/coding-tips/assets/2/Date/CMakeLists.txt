project(My-Date)

add_library(Date "Date.hpp" "Date.cpp")
target_include_directories(Date INTERFACE .)
