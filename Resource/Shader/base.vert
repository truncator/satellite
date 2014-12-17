#version 330

uniform mat4 projection_view;
uniform mat4 model;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 o_uv;

void main()
{
	o_uv = uv;

	gl_Position = projection_view * vec4(position, 1.0);
}
