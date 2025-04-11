# 递归遍历本文件夹下的所有cpp文件, 并保存到WRAPPER变量中
file(GLOB_RECURSE WRAPPER ./ *.cpp)

# 将WRAPPER中的所有cpp文件编译为wrapper这个lib库
add_library(wrapper ${WRAPPER})
