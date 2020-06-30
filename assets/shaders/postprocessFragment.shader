
#version 330 core

uniform sampler2D sampler2d;

in vec2 texture_uv;
out vec4 fragment_color;

float rand(vec2 co) {
	return (fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453)) * 0.15f;
}

void main()
{
	vec3 color = texture(sampler2d, texture_uv.st).rgb;	
	fragment_color = vec4(vec3(color.r + rand(texture_uv.st), color.g + rand(texture_uv.st), color.b + rand(texture_uv.st)), 0.2);

}








