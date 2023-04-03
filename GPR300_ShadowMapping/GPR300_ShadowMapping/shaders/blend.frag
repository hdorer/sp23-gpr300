#version 450

out vec4 FragColor;

in vec2 Uv;

uniform sampler2D scene;
uniform sampler2D blur;

uniform bool bloom;
uniform float exposure;

void main() {
	const float gamma = 2.2;

	vec3 color = texture(scene, Uv).rgb;
	vec3 bloomColor = texture(blur, Uv).rgb;
	
	if(bloom) {
		color += bloomColor;
	}

	vec3 result = vec3(1.0) - exp(-color * exposure);
	result = pow(result, vec3(1.0 / gamma));

	FragColor = vec4(result, 1.0);
}