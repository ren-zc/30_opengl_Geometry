#version 460 core
in vec3 color;
in vec2 uv;
out vec4 FragColor;

uniform sampler2D sampler;

void main()
{
    FragColor = texture(sampler, uv);
}
