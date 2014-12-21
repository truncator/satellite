#version 330

uniform sampler2D tex;

in vec2 o_uv;

out vec4 frag_color;

void main()
{
	vec4 color = texture(tex, o_uv);

	if (color.a < 0.5)
		discard;

	frag_color = color;
}
