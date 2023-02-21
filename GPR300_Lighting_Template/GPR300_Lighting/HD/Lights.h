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
	float linearAttenuation;
};

struct DirectionalLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
};

struct SpotLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
	float angularAttenuation;
	float minAngle;
	float maxAngle;
};