#version 460 core
// location也可以动态获取: 1. 在vbo属性写入vao之前, 
// 先使用glGetAttribLocation获取到属性编号
// 再使用此变化去把vbo属性写入vao中
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aUV;
out vec3 color;
out vec2 uv;

// 接收矩阵
uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    // 矩阵*坐标, 如果是多个矩阵: 矩阵*矩阵*坐标, 坐标在最右边, 从右往左算
    vec4 position = projectionMatrix * viewMatrix * transform * vec4(aPos, 1.0);
    gl_Position = position;

    // 输出color和uv
    // color = aColor;
    uv = aUV;
}
