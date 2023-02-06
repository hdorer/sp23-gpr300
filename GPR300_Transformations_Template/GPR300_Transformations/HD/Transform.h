#pragma once

#include "glm/glm.hpp"

class Transform {
	public:
		Transform();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);
		void setRotation(glm::vec3 rotation);
		void setRotation(float x, float y, float z);
		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);
		void setScale(float scaleFactor);
		
		glm::mat4 getModelMatrix();
	private:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::mat4 getRotationMatrix();
		glm::mat4 getScaleMatrix();
		glm::mat4 getTranslationMatrix();
};