#version 130

in vec2 position2;
out vec4 outBuffer;

uniform sampler2D colorTexture;

void main()
{
	ivec2 size = textureSize(colorTexture, 0);
	//ivec2 loc = ivec2(gl_FragCoord.xy);
	//outBuffer = vec4(texelFetch(colorTexture, loc, 0).xyz, 1.0);
	outBuffer = vec4(float(size.x) / 5.0, 0.0, 0.0, 1.0);
	//outBuffer = vec4(position2 + 1.0, 0.0, 1.0);
}


