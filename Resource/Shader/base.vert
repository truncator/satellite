#version 330

uniform mat4 projection_view;
uniform mat4 model;

uniform vec2 tex_offset;
uniform vec2 tex_size;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 o_uv;

void main()
{
	o_uv = tex_offset + tex_size * uv;

	gl_Position = projection_view * model * vec4(position, 1.0);
}
