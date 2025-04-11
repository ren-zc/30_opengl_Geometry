# 递归遍历本文件夹下的所有cpp文件, 并保存到APP变量中
file(GLOB_RECURSE APP ./ *.cpp)

# 将WRAPPER中的所有cpp文件编译为app这个lib库
add_library(app ${APP})
