#pragma once

#include "glm/glm.hpp"

class Transform {
	public:
		glm::mat4 getModelMatrix();
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
};