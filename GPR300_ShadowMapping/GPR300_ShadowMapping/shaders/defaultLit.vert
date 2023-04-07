#version 450                          

layout (location = 0) in vec3 vPos;  
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUv;
layout (location = 3) in vec3 vTangent;

uniform mat4 _Model;
uniform mat4 _View;
uniform mat4 _Projection;

out vec3 Position;
out vec3 Normal;
out vec2 Uv;
out mat3 TBN;

void main(){
    Position = vPos;
    Normal = vNormal;
    Uv = vUv;

    vec3 bitangent = cross(vTangent, vNormal);
    TBN = mat3(
        vTangent.x, vTangent.y, vTangent.z,
        bitangent.x, bitangent.y, bitangent.z,
        vNormal.x, vNormal.y, vNormal.z
    );

    gl_Position = _Projection * _View * _Model * vec4(vPos,1);
}
