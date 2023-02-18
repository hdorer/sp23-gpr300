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

struct DirectionalLight {
    vec3 position;
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

out vec4 FragColor;

in vec3 Normal;

uniform vec3 cameraPosition;

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

    float ambientLightLevel = 0.8;
    vec3 ambient = ambientLightLevel * dLight.color;

    vec3 directionToLight = normalize(dLight.position - vs_out.worldPosition);
    float diffuseAmount = max(dot(normal, directionToLight), 0.0);
    vec3 diffuse = diffuseAmount * dLight.color;

    float specularStrength = 0.8;
    vec3 viewDirection = normalize(cameraPosition - vs_out.worldPosition);
    vec3 reflectDirection = reflect(-directionToLight, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = specularStrength * specularAmount * dLight.color;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
