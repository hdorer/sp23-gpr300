#pragma once

#include "glm/glm.hpp"

class Transform {
	public:
		Transform();
		
		glm::mat4 getModelMatrix();
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::mat4 getRotationMatrix();
		glm::mat4 getScaleMatrix();
		glm::mat4 getTranslationMatrix();
};