#pragma once

#include "glm/glm.hpp"

class Camera {
	public:
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();
	private:
		float fov;
		bool orthographic;
		float orthographicSize;
		glm::vec3 position;
		glm::vec3 target;

		glm::mat4 ortho(float height, float aspectRatio, float nearPlane, float farPlane);
		glm::mat4 perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
};