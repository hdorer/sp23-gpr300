#version 450                          
out vec4 FragColor;

in vec3 Normal;
in vec2 Uv;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    vec4 color = texture(texture1, Uv);
    FragColor = color;
}
