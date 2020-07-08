VERTEX_SHADER

attribute vec3 a_position;

void main()
{
    gl_Position = vec4(a_position, 1.);
}

FRAGMENT_SHADER

precision mediump float;

uniform vec4 u_color;

void main()
{
    gl_FragColor = u_color;
}