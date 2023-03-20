#version 450                          

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float ambientLevel;
    float minRadius;
    float maxRadius;
};

#define MAX_POINT_LIGHTS 5

struct Material {
    vec3 color;
    float ambientK;
    float diffuseK;
    float specularK;
    float shininess;
};

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 Uv;
in mat3 TBN;

uniform vec3 cameraPosition;

uniform PointLight pLights[MAX_POINT_LIGHTS];
uniform int numPointLights = 0;

uniform Material material;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform sampler2D normalMap;

vec4 getAmbient(float ambientLevel, vec3 color, float intensity) {
    return (vec4(material.color, 1.0) * material.ambientK) * ambientLevel * (vec4(color, 1.0) * intensity);
}

vec4 getDiffuse(vec3 position, vec3 direction, vec3 color, float intensity, vec3 normal) { // pass in directionToLight as a parameter.
    float diffuseAmount = max(dot(normal, direction), 0.0);
    return (vec4(material.color, 1.0) * material.specularK) * diffuseAmount * (vec4(color, 1.0) * intensity); // change lightColor to a light diffuse vec3 or something
}

vec4 getSpecular(vec3 position, vec3 direction, vec3 color, float intensity, vec3 normal) { // pass in directionToLight as a parameter
    vec3 viewDirection = normalize(cameraPosition - Position);
    vec3 reflectDirection = reflect(-direction, normal);
    vec3 halfVector = normalize(viewDirection + reflectDirection);
    
    float specularAmount = pow(max(dot(viewDirection, halfVector), 0.0), material.shininess);
    return (vec4(material.color, 1.0) * material.specularK) * specularAmount * (vec4(color, 1.0) * intensity);
}

float linearAttenuation(float intensity, vec3 position, float minRadius, float maxRadius) {
    float distanceToLight = distance(position, Position);
    
    return intensity * min(max((maxRadius - distanceToLight) / (maxRadius - minRadius), 0), 1);
}

vec4 pointLightLevel(PointLight light, vec3 normal) {
    float intensity = linearAttenuation(light.intensity, light.position, light.minRadius, light.maxRadius);
    vec3 directionToLight = normalize(light.position - Position);

    vec4 ambient = getAmbient(light.ambientLevel, light.color, light.intensity);
    vec4 diffuse = getDiffuse(light.position, directionToLight, light.color, intensity, normal);
    vec4 specular = getSpecular(light.position, directionToLight, light.color, intensity, normal);

    return ambient + diffuse + specular;
}

void main(){
    vec4 color = texture(texture1, Uv);
    vec3 rgbNormal = texture(normalMap, Uv).rgb;
    rgbNormal = rgbNormal * 2.0 - 1.0;
    rgbNormal = normalize(TBN * rgbNormal);
    // vec4 color = vec4(Uv.x, Uv.y, 0.0, 1.0);

    vec4 result = vec4(0);

    for(int i = 0; i < numPointLights; i++) {
        result += pointLightLevel(pLights[i], rgbNormal) * color;
    }

    FragColor = result;
}
