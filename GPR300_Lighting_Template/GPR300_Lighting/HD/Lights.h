#pragma once

#include "../EW/Transform.h"
#include "glm/glm.hpp"

#include "../EW/Transform.h"
#include "glm/glm.hpp"

struct PointLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
	float minRadius;
	float maxRadius;
};

struct DirectionalLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;

	glm::vec3 direction() {
		float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		float y = sin(glm::radians(transform.rotation.x));
		float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

		return glm::normalize(glm::vec3(x, y, z));
	}
};

struct SpotLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
	float angularAttenuation;
	float minAngle;
	float maxAngle;

	glm::vec3 direction() {
		float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		float y = sin(glm::radians(transform.rotation.x));
		float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

		return glm::normalize(glm::vec3(x, y, z));
	}
};