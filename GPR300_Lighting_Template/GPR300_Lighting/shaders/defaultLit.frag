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

#define MAX_POINTLIGHTS 8

uniform PointLight _PointLights[MAX_POINTLIGHTS];
uniform Material _Material;

uniform int _NumPointLights = 4;

vec3 calcDiffuse(vec3 toLight, vec3 normal, vec3 lightColor) {
    // return amount of diffuse light 
    return vec3(0);
}

// vec3 calcSpecular

vec3 calcDirectionalLight(DirectionalLight light) {
    return vec3(0);
}

vec3 calcPointLight(PointLight light) {
    return vec3(0);
}

void main(){         
    vec3 normal = normalize(vs_out.worldNormal);
    FragColor = vec4(abs(normal),1.0f);
}
