#version 400

in vec2 texcoord;
in vec3 position;

out vec2 Texcoord;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 proj;

void main(){
	Texcoord = texcoord;
	gl_Position =proj*view* trans* vec4(position , 1.0);
}