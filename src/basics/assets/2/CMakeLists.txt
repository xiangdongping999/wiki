project(CPP-Multi-File-Demo)

add_executable(single_file_demo "single_file_demo.cpp")

# 逐一指明目标 demo 需要的源文件
# add_executable(demo "demo.cpp" "Date/Date.hpp" "Date/Date.cpp")

# 或者：

# 将 Date 生成为一个 Library
# 并作为子项目引入
# 子目录 Date 中的 CMakeLists.txt 包含生成 Date 这个 library 的目标

add_subdirectory(Date)

add_executable(demo "demo.cpp")
target_link_libraries(demo Date)
