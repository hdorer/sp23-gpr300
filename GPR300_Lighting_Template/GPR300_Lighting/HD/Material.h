#pragma once

#include "../EW/Shader.h"
#include "glm/glm.hpp"

struct Material {
	glm::vec3 color = glm::vec3(1.0, 0.6, 0.8);
	float ambientK = 0.5;
	float diffuseK = 0.2;
	float specularK = 0.8;
	float shininess = 256;

	void setShaderValues(Shader* shader) {
		shader->setVec3("material.color", color);
		shader->setFloat("material.ambientK", ambientK);
		shader->setFloat("material.diffuseK", diffuseK);
		shader->setFloat("material.specularK", specularK);
		shader->setFloat("material.shininess", shininess);
	}
};