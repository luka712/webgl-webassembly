VERTEX_SHADER
#version 300 es

layout(location = 0) in vec3 a_position;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);
}

FRAGMENT_SHADER
#version 300 es

precision mediump float;

uniform float u_ambient_strength;
uniform vec3 u_ambient_color;

uniform vec4 u_diffuse;

out vec4 color;

void main()
{
    vec3 ambient = u_ambient_strength * u_ambient_color;
    color = vec3(u_diffuse.xyz * ambient, 1.0);
}