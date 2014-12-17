#version 330

uniform mat4 projection_view;
uniform mat4 model;

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = projection_view * model * vec4(position, 1.0);
}
