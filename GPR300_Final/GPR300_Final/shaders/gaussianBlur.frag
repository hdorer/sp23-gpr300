// Code adapted from Learn OpenGL article on bloom: https://learnopengl.com/Advanced-Lighting/Bloom

#version 450

out vec4 FragColor;

in vec2 Uv;

uniform sampler2D image;

uniform bool horizontal;
uniform float weight[4];

void main() {
	vec2 texOffset = 1.0 / textureSize(image, 0);
	vec3 result = texture(image, Uv).rgb * weight[0];

	if(horizontal) {
		for(int i = 1; i < 5; ++i) {
			result += texture(image, Uv + vec2(texOffset.x * i, 0.0)).rgb * weight[i];
			result += texture(image, Uv - vec2(texOffset.x * i, 0.0)).rgb * weight[i];
		}
	} else {
		for(int i = 1; i < 5; ++i) {
			result += texture(image, Uv + vec2(texOffset.y * i, 0.0)).rgb * weight[i];
			result += texture(image, Uv - vec2(texOffset.y * i, 0.0)).rgb * weight[i];
		}
	}

	FragColor = vec4(result, 1.0);
}