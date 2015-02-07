#version 330

uniform vec3 line_color;

out vec4 frag_color;

void main()
{
	frag_color = vec4(line_color.rgb, 1.0);
}
