#version 420 core
#define FRAG_COLOR		0

in block
{
	flat int DrawID;
} In;

layout(location = FRAG_COLOR, index = 0) out vec4 Color;

const vec4 Color[] = {
	vec4(1.0, 0.5, 0.0, 1.0),
	vec4(0.0, 0.5, 1.0, 1.0)
};

void main()
{
	Color = Color[In.DrawID];
}