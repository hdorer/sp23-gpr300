#version 450                          
out vec4 FragColor;

in vec3 Normal;
in vec2 Uv;

void main(){         
    FragColor = vec4(abs(Normal),1.0f);
}
