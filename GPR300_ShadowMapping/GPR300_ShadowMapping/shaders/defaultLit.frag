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

const float MIN_BIAS = 0.005;
const float MAX_BIAS = 0.015;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 EffectColor;

in vec3 Position;
in vec3 Normal;
in vec2 Uv;
in mat3 TBN;
in vec4 lightSpacePos;

uniform vec3 cameraPosition;

uniform DirectionalLight dLight;
uniform Material material;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D normalMap;
uniform sampler2D shadowMap;

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

float shadow(vec3 normal, vec3 direction) {
    float totalShadow = 0;
    vec2 texelOffset = 1.0 / textureSize(shadowMap, 0);

    vec3 sampleCoord = lightSpacePos.xyz / lightSpacePos.w;
    sampleCoord = sampleCoord * 0.5 + 0.5;
    
    float shadowMapDepth;
    float bias = max(MAX_BIAS * (1.0 - dot(normal, direction)), MIN_BIAS);
    float depth = sampleCoord.z - bias;
    
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            shadowMapDepth = texture(shadowMap, sampleCoord.xy + vec2(x, y) * texelOffset).r;
            totalShadow += step(shadowMapDepth, depth);
        }
    }

    totalShadow /= 9.0;

    return totalShadow;
}

vec4 directionalLightLevel(DirectionalLight light, vec3 normal) {
    vec4 ambient = getAmbient(light.ambientLevel, light.color, light.intensity);
    vec4 diffuse = getDiffuse(light.position, -light.direction, light.color, light.intensity, normal);
    vec4 specular = getSpecular(light.position, -light.direction, light.color, light.intensity, normal);

    return ambient + (diffuse + specular) * (1.0 - shadow(normal, light.direction));
}

void main(){
    vec4 color = texture(texture1, Uv);
    vec3 rgbNormal = texture(normalMap, Uv).rgb;
    rgbNormal = rgbNormal * 2.0 - 1.0;
    rgbNormal = normalize(TBN * rgbNormal);

    vec4 result = vec4(0);

    result += directionalLightLevel(dLight, rgbNormal) * color;

    FragColor = result;

    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0) {
        EffectColor = vec4(FragColor.rgb, 1.0);
    } else {
        EffectColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
