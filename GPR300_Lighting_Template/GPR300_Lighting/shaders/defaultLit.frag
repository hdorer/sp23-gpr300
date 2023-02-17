#version 450                          
out vec4 FragColor;

in vec3 Normal;

in struct Vertex {
    vec3 worldPosition;
    vec3 worldNormal;
} vs_out;

struct Material {
    float ambientK;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float linearAttenuation;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

struct SpotLight {
    vec3 position;
    vec3 color;
    vec3 direction;
    float intensity;
    float linearAttenuation;
    float minAngle;
    float maxAngle;
};

uniform DirectionalLight dLight;

uniform Material material;

//vec4 calcDirectionalLight(DirectionalLight light) {
//    float diffuseAmount = material.ambientK * min(dot(light.direction, vs_out.worldNormal), 0) * light.intensity;
//    vec3 diffuse = vec3(diffuseAmount * light.color.x, diffuseAmount * light.color.y, diffuseAmount * light.color.z);
//
//    float specularAmount = 1.0 - material.ambientK * 
//
//    return vec4(diffuse.x, diffuse.y, diffuse.z, 0.0);
//}

//vec3 calcPointLight(PointLight light) {
//    return vec3(0);
//}

void main(){         
    vec3 normal = normalize(vs_out.worldNormal);
    vec3 objectColor = abs(normal);
    FragColor = vec4(objectColor, 1.0);
}
