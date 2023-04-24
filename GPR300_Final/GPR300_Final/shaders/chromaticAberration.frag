#version 450

out vec4 FragColor;

uniform sampler2D sceneTexture;

uniform float rOffset;
uniform float gOffset;
uniform float bOffset;

uniform vec2 focusPoint;

uniform bool enabled;

void main() {
	vec2 texSize = textureSize(sceneTexture, 0).xy;
	vec2 texCoords = gl_FragCoord.xy / texSize;

	vec2 direction = texCoords - focusPoint;

	vec3 result = vec3(1.0);
	if(enabled) {
		result.r = texture(sceneTexture, texCoords + (direction * vec2(rOffset))).r;
		result.g = texture(sceneTexture, texCoords + (direction * vec2(gOffset))).g;
		result.b = texture(sceneTexture, texCoords + (direction * vec2(bOffset))).b;
	} else {
		result = texture(sceneTexture, texCoords).rgb;
	}

	FragColor = vec4(result, 1.0);
}