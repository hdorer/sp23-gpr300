#pragma once

#include "glm/glm.hpp"

struct Material {
	glm::vec3 color;
	float ambientK;
	float diffuseK;
	float specularK;
	float shininess;
};