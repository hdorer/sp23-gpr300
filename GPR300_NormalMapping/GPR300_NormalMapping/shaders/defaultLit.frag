#version 450                          
out vec4 FragColor;

in vec3 Normal;
in vec2 Uv;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform sampler2D normalMap;

void main(){
    vec4 color = texture(texture1, Uv);
    vec3 rgbNormal = texture(normalMap, Uv).rgb;
    // vec4 color = vec4(Uv.x, Uv.y, 0.0, 1.0);
    FragColor = vec4(rgbNormal, 1);
}
