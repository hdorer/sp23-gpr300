#pragma once

#include "../EW/Transform.h"
#include "glm/glm.hpp"

#include "../EW/Transform.h"
#include "glm/glm.hpp"

struct PointLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float linearAttenuation;
};

struct DirectionalLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
};

struct SpotLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float linearAttenuation;
	float minAngle;
	float maxAngle;
};