#version 130

in vec2 position;
out vec2 position2;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	position2 = position;
}


