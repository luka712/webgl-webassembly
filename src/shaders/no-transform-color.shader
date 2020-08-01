VERTEX_SHADER
#version 300 es

layout(location = 0) in vec3 a_position;


void main()
{
    gl_Position = vec4(a_position, 1.);
}

FRAGMENT_SHADER
#version 300 es

precision mediump float;

uniform vec4 u_color;

out vec4 color;

void main()
{
    color = u_color;
}