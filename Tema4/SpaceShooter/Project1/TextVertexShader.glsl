#version 400

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texcoord;

out vec2 Texcoord;

void main(){
	Texcoord = texcoord;

	vec2 vertexPos = position-vec2(400,300);
	vertexPos /= vec2(400,300);
	gl_Position =vec4(vertexPos , 0.0,1.0);
}