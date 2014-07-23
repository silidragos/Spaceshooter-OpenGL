#version 400

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D basic_texture;

void main(){
	outColor = vec4(-0.2,-0.2,0.0,0.0) + texture(basic_texture, Texcoord);
}