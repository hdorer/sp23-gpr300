#version 450

out vec4 FragColor;

const float FOCUS_POINT_INDICATOR_RADIUS = 0.003;

uniform sampler2D sceneTexture;

uniform vec2 rOffset;
uniform vec2 gOffset;
uniform vec2 bOffset;

uniform vec2 focusPoint;

uniform bool enabled;
uniform bool showFocusPoint;

void main() {
	vec2 texSize = textureSize(sceneTexture, 0).xy;
	vec2 texCoords = gl_FragCoord.xy / texSize;

	vec2 direction = texCoords - focusPoint;

	vec3 result = texture(sceneTexture, texCoords).rgb;

	if(enabled) {
		if(showFocusPoint && length(texCoords - focusPoint) <= FOCUS_POINT_INDICATOR_RADIUS) {
			result = vec3(1.0, 0.0, 0.0);
		} else {
			result.r = texture(sceneTexture, texCoords + (direction * rOffset)).r;
			result.g = texture(sceneTexture, texCoords + (direction * gOffset)).g;
			result.b = texture(sceneTexture, texCoords + (direction * bOffset)).b;
		}
	}

	FragColor = vec4(result, 1.0);
}