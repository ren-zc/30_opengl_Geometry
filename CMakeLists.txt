# 需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

# 本工程的名字
project(openglTest01)

# 本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

# 往项目中添加一个全局的预编译宏, 全局检查开关
add_definitions(-DDEBUG)

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

# 添加头文件目录
include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)

# 添加lib库目录
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

# 添加wrapper目录
add_subdirectory(wrapper)

# 添加目录application
add_subdirectory(application)

# 添加目录application
add_subdirectory(glframwork)

# 本工程主程序文件及输出程序名称
add_executable(openglTest01 "main.cpp" "glad.c" "glm_test.cpp")

target_link_libraries(openglTest01 glfw3.lib wrapper app fw)
