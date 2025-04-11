#version 460 core
// locationҲ���Զ�̬��ȡ: 1. ��vbo����д��vao֮ǰ, 
// ��ʹ��glGetAttribLocation��ȡ�����Ա��
// ��ʹ�ô˱仯ȥ��vbo����д��vao��
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aUV;
out vec3 color;
out vec2 uv;

// ���վ���
uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    // ����*����, ����Ƕ������: ����*����*����, ���������ұ�, ����������
    vec4 position = projectionMatrix * viewMatrix * transform * vec4(aPos, 1.0);
    gl_Position = position;

    // ���color��uv
    // color = aColor;
    uv = aUV;
}
