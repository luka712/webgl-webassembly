VERTEX_SHADER

attribute vec3 a_position;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_projection  * u_view * u_transform * vec4(a_position, 1.);
}

FRAGMENT_SHADER

precision mediump float;

uniform vec4 u_color;

void main()
{
    gl_FragColor = u_color;
}