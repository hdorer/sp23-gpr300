#pragma once

#include "glm/glm.hpp"

class Camera {
	public:
		Camera();

		float getFov();
		bool getOrthographic();
		float getOrthographicSize();

		float getNearPlane();
		float getFarPlane();
		
		glm::vec3 getPosition();
		glm::vec3 getTarget();

		void setFov(float fov);
		void setOrthographic(bool orthographic);
		void setOrthographicSize(float orthographicSize);

		void setNearPlane(float nearPlane);
		void setFarPlane(float farPlane);
		
		void setPosition(glm::vec3 position);
		void setPosition(float x, float y, float z);
		void setTarget(glm::vec3 target);
		void setTarget(float x, float y, float z);

		glm::mat4 getProjectionMatrix(float screenWidth, float screenHeight);
		glm::mat4 getViewMatrix();

		void drawGUI();
	private:
		float fov;
		bool orthographic;
		float orthographicSize;

		float nearPlane;
		float farPlane;
		
		glm::vec3 position;
		glm::vec3 target;
		
		glm::mat4 getTranslationMatrix();
		glm::mat4 lookAt(glm::vec3 targetPos, glm::vec3 cameraPos, glm::vec3 up);
		glm::mat4 ortho(float height, float aspectRatio, float nearPlane, float farPlane);
		glm::mat4 perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
};