#version 450

out vec4 FragColor;

uniform sampler2D sceneTexture;

uniform vec3 colorOffsets;

uniform vec2 focusPoint;

uniform bool enabled;
uniform bool showFocusPoint;

void main() {
	vec2 texSize = textureSize(sceneTexture, 0).xy;
	vec2 texCoords = gl_FragCoord.xy / texSize;

	vec2 direction = texCoords - focusPoint;

	vec3 result = texture(sceneTexture, texCoords).rgb;

	if(enabled) {
		if(showFocusPoint && length(texCoords - focusPoint) <= 0.003) {
			result = vec3(1.0, 0.0, 0.0);
		} else {
			result.r = texture(sceneTexture, texCoords + (direction * vec2(colorOffsets.r))).r;
			result.g = texture(sceneTexture, texCoords + (direction * vec2(colorOffsets.g))).g;
			result.b = texture(sceneTexture, texCoords + (direction * vec2(colorOffsets.b))).b;
		}
	}

	FragColor = vec4(result, 1.0);
}