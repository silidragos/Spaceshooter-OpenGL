#version 400

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D basic_texture;
uniform vec3 reddish;

void main(){
	outColor = texture(basic_texture, Texcoord)*vec4(reddish,1.0f);
}