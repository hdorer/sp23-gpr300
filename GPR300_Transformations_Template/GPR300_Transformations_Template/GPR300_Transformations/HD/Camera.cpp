#include "Camera.h"

glm::mat4 Camera::getProjectionMatrix() {
	if (orthographic) {
		return ortho(orthographicSize, 16 / 9, nearPlane, farPlane);
	} else {
		return perspective(fov, 16 / 9, nearPlane, farPlane);
	}
}

glm::mat4 Camera::getTranslationMatrix() {
	return glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-position.x, -position.y, -position.z, 1
	);
}

glm::mat4 Camera::getViewMatrix(glm::vec3 targetPos) {
	return lookAt(targetPos, position, glm::vec3(0, 1, 0)) * getTranslationMatrix();
}

glm::mat4 Camera::lookAt(glm::vec3 targetPos, glm::vec3 cameraPos, glm::vec3 worldUp) {
	glm::vec3 forward = glm::normalize(cameraPos - targetPos);
	glm::vec3 right = glm::normalize(glm::cross(worldUp, forward));
	glm::vec3 up = glm::normalize(glm::cross(forward, right));

	return glm::mat4(
		right.x, up.x, forward.x, 0,
		right.y, up.y, forward.y, 0,
		right.z, up.z, forward.z, 0,
		0, 0, 0, 1
	);
}

glm::mat4 Camera::ortho(float height, float aspectRatio, float nearPlane, float farPlane) {
	float width = fov * aspectRatio;

	float rightBounds = width / 2;
	float topBounds = height / 2;
	float leftBounds = -rightBounds;
	float bottomBounds = -topBounds;

	return glm::mat4(
		2 / (rightBounds - leftBounds), 0, 0, 0,
		0, 2 / (topBounds - bottomBounds), 0, 0,
		0, 0, -2 / (farPlane - nearPlane), 0,
		-(rightBounds + leftBounds) / (rightBounds - leftBounds), -(topBounds + bottomBounds) / (topBounds - bottomBounds), -(farPlane + nearPlane) / (farPlane - nearPlane), 1
	);
}

glm::mat4 Camera::perspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
	float c = tan(fov / 2);
	
	return glm::mat4(
		1 / (aspectRatio * c), 0, 0, 0,
		0, 1 / c, 0, 0,
		0, 0, -((farPlane + nearPlane) / (farPlane - nearPlane)), -1,
		0, 0, -((2 * farPlane * nearPlane) / (farPlane - nearPlane)), 1
	);
}