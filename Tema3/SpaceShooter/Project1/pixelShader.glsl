#version 400

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D basic_texture;

void main(){
         outColor = texture(basic_texture, Texcoord);
      }