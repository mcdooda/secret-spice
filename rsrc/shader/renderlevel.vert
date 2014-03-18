#version 130

uniform mat4 vpMatrix;

in vec2 position;

void main()
{
	gl_Position = vpMatrix * vec4(position, 0.0, 1.0);
}


