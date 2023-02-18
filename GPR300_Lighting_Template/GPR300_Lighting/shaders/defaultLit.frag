#version 450                          

in struct Vertex {
    vec3 worldPosition;
    vec3 worldNormal;
} vs_out;

struct Material {
    vec3 color;
    float ambientK;
    float diffuseK;
    float specularK;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float linearAttenuation;
};

//struct DirectionalLight {
//    vec3 position;
//    vec3 direction;
//    vec3 color;
//    float intensity;
//};

//struct SpotLight {
//    vec3 position;
//    vec3 color;
//    vec3 direction;
//    float intensity;
//    float linearAttenuation;
//    float minAngle;
//    float maxAngle;
//};

out vec4 FragColor;

in vec3 Normal;

uniform vec3 cameraPosition;

uniform PointLight pLight;

uniform Material material;

vec3 getAmbient(vec3 lightColor) {
    float ambientLightLevel = 0.8;
    return ambientLightLevel * lightColor;
}

vec3 getSpecular(vec3 lightPosition, vec3 lightColor) {
    vec3 normal = normalize(vs_out.worldNormal);
    vec3 directionToLight = normalize(lightPosition - vs_out.worldPosition);

    float diffuseAmount = max(dot(normal, directionToLight), 0.0);
    return diffuseAmount * lightColor;
}

vec3 getDiffuse(vec3 lightPosition, vec3 lightColor) {
    vec3 normal = normalize(vs_out.worldNormal);
    vec3 directionToLight = normalize(lightPosition - vs_out.worldPosition);

    float specularStrength = 0.8;
    vec3 viewDirection = normalize(cameraPosition - vs_out.worldPosition);
    vec3 reflectDirection = reflect(-directionToLight, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    return specularStrength * specularAmount * lightColor;
}

void main(){         
    vec3 normal = normalize(vs_out.worldNormal);
    vec3 objectColor = abs(normal);    

    vec3 result = (getAmbient(pLight.color) + getDiffuse(pLight.position, pLight.color) + getSpecular(pLight.position, pLight.color)) * objectColor;
    FragColor = vec4(result, 1.0);
}
