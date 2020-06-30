#version 330 core


uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;

layout(location = 0) in vec3 vertex;

out vec3 texture_coords;

void main()
{
	texture_coords = vec3(vertex.x, -vertex.y, vertex.z);
	gl_Position = projection_matrix * model_view_matrix * vec4(vertex, 1.0);
}