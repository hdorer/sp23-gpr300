#version 450                          

struct DirectionalLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float ambientLevel;
};

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
    float ambientLevel;
    float minRadius;
    float maxRadius;
};

#define MAX_POINT_LIGHTS 5

struct SpotLight {
    vec3 position;
    vec3 color;
    vec3 direction;
    float intensity;
    float ambientLevel;
    float minAngle;
    float maxAngle;
};

#define MAX_SPOT_LIGHTS 5 

in struct Vertex {
    vec3 worldPosition;
    vec3 worldNormal;
} vs_out;


out vec4 FragColor;

in vec3 Normal;

uniform vec3 cameraPosition;

uniform PointLight pLights[MAX_POINT_LIGHTS];
uniform int numPointLights = 0;

uniform SpotLight sLights[MAX_SPOT_LIGHTS];
uniform int numSpotLights = 0;

uniform DirectionalLight dLight;

uniform Material material;

vec3 getAmbient(float ambientLevel, vec3 color, float intensity) {
    return (material.color * material.ambientK) * ambientLevel * (color * intensity);
}

vec3 getDiffuse(vec3 position, vec3 direction, vec3 color, float intensity) { // pass in directionToLight as a parameter.
    vec3 normal = normalize(vs_out.worldNormal);

    float diffuseAmount = max(dot(normal, direction), 0.0);
    return (material.color * material.specularK) * diffuseAmount * (color * intensity); // change lightColor to a light diffuse vec3 or something
}

vec3 getSpecular(vec3 position, vec3 direction, vec3 color, float intensity) { // pass in directionToLight as a parameter
    vec3 normal = normalize(vs_out.worldNormal);

    vec3 viewDirection = normalize(cameraPosition - vs_out.worldPosition);
    vec3 reflectDirection = reflect(-direction, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    return (material.color * material.specularK) * specularAmount * (color * intensity);
}

float linearAttenuation(float intensity, vec3 position, float minRadius, float maxRadius) {
    float distanceToLight = distance(position, vs_out.worldPosition);
    
    return intensity * min(max((maxRadius - distanceToLight) / (maxRadius - minRadius), 0), 1);
}

float angularAttenuation(float intensity, vec3 position, vec3 direction, float minAngle, float maxAngle) {
    vec3 directionToFrag = normalize(vs_out.worldPosition - position);
    float cosAngle = dot(normalize(direction), directionToFrag);
    float cosMinAngle = cos(radians(minAngle));
    float cosMaxAngle = cos(radians(maxAngle));

    return intensity * clamp((cosAngle - cosMaxAngle) / (cosMinAngle - cosMaxAngle), 0, 1);
}

vec3 pointLightLevel(PointLight light) {
    float intensity = linearAttenuation(light.intensity, light.position, light.minRadius, light.maxRadius);
    vec3 directionToLight = normalize(light.position - vs_out.worldPosition);

    vec3 ambient = getAmbient(light.ambientLevel, light.color, light.intensity);
    vec3 diffuse = getDiffuse(light.position, directionToLight, light.color, intensity);
    vec3 specular = getSpecular(light.position, directionToLight, light.color, intensity);

    return ambient + diffuse + specular;
}

vec3 spotLightLevel(SpotLight light) {
    float intensity = angularAttenuation(light.intensity, light.position, light.direction, light.minAngle, light.maxAngle);
    vec3 directionToLight = normalize(light.position - vs_out.worldPosition);

    vec3 ambient = getAmbient(light.ambientLevel, light.color, light.intensity);
    vec3 diffuse = getDiffuse(light.position, directionToLight, light.color, intensity);
    vec3 specular = getSpecular(light.position, directionToLight, light.color, intensity);

    return ambient + diffuse + specular;
}

vec3 directionalLightLevel(DirectionalLight light) {
    vec3 ambient = getAmbient(light.ambientLevel, light.color, light.intensity);
    vec3 diffuse = getDiffuse(light.position, light.direction, light.color, light.intensity);
    vec3 specular = getSpecular(light.position, light.direction, light.color, light.intensity);

    return ambient + diffuse + specular;
}

void main(){         
    vec3 normal = normalize(vs_out.worldNormal);
    vec3 objectColor = abs(normal);
    
    vec3 result = vec3(0);

    for(int i = 0; i < numPointLights; i++) {
        result += pointLightLevel(pLights[i]) * objectColor;
    }
    
    for(int i = 0; i < numSpotLights; i++) {
        result += spotLightLevel(sLights[i]) * objectColor;
    }

    result += directionalLightLevel(dLight) * objectColor;

    FragColor = vec4(result, 1.0);
}
