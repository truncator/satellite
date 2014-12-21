#version 330

uniform mat4 projection_view;
uniform mat4 model;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

out vec2 v_uv;
out vec3 v_color;

void main()
{
	v_color = color;
	v_uv = uv;

	gl_Position = projection_view * vec4(position.xy, 0.0, 1.0);
	gl_Position.z = position.z;
}
