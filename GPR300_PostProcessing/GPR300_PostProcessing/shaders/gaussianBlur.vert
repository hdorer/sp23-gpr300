#version 450

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vUv;

out vec2 Uv;

void main() {
	Uv = vUv;
	gl_Position = vec4(vPos, 1.0);
}