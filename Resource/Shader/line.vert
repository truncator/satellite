#version 330

uniform mat4 projection_view;

uniform vec2 line_start;
uniform vec2 line_end;

void main()
{
	vec2 verts[2] = vec2[2] (
			line_start,
			line_end
	);
	vec2 position = verts[gl_VertexID];

	gl_Position = projection_view * vec4(position.xy, 0.0, 1.0);
}
