#version 400

in vec2 texcoord;
in vec3 position;

out vec2 Texcoord;

void main(){
Texcoord = texcoord;
gl_Position = vec4(position,1.0f);
}