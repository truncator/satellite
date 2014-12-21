#version 330

uniform sampler2D tex;

in vec2 v_uv;
in vec3 v_color;

out vec4 frag_color;

void main()
{
	vec4 color = texture(tex, v_uv);

	if (color.a < 0.5)
		discard;

	color.rgb *= v_color;

	frag_color = vec4(color.rgb, 1.0);
}
