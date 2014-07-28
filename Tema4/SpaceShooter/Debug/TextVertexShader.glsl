#version 400

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texcoord;

out vec2 Texcoord;

uniform vec2 resolution;

void main(){
	Texcoord = texcoord;

	vec2 vertexPos = position-vec2(resolution.x/2,resolution.y/2);
	vertexPos /= vec2(resolution.x/2,resolution.y/2);
	gl_Position =vec4(vertexPos , 0.0,1.0);
}