#version 330

uniform sampler2D tex;

in vec2 o_uv;

out vec4 frag_color;

void main()
{
	frag_color = texture(tex, o_uv);
}
