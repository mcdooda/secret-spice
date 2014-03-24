#version 130

#define M_PI 3.1415926535897932384626433832795

uniform sampler2D screen;

in vec2 uv2;

out vec4 outColor;

void main()
{
	float radius = 0.005;
	float initAngle = 0.0;
	vec3 angles = vec3(initAngle, initAngle + M_PI * 2.0 / 3.0, initAngle - M_PI * 2.0 / 3.0);
	outColor = (texture(screen, uv2)
	         + vec4(texture(screen, uv2 + vec2(cos(angles.r), sin(angles.r)) * radius).r, 0.0, 0.0, 1.0)
	         + vec4(0.0, texture(screen, uv2 + vec2(cos(angles.g), sin(angles.g)) * radius).g, 0.0, 1.0)
	         + vec4(0.0, 0.0, texture(screen, uv2 + vec2(cos(angles.b), sin(angles.b)) * radius).b, 1.0)) / 2.0;
}


