#version 400

in vec2 texcoord;
in vec3 position;

out vec2 Texcoord;

uniform mat4 trans;

void main(){
Texcoord = texcoord;
gl_Position = trans*vec4(position,1.0f);
}