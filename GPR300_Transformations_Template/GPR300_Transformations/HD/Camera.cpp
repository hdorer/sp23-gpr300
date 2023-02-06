#include "Camera.h"

Camera::Camera() {
	fov = 90;
	orthographic = false;
	orthographicSize = 5;
	
	nearPlane = 0.5;
	farPlane = 10;

	position = glm::vec3(0);
	target = glm::vec3(0);
}

float Camera::getFarPlane() {
	return farPlane;
}

float Camera::getFov() {
	return fov;
}

bool Camera::getOrthographic() {
	return orthographic;
}

float Camera::getOrthographicSize() {
	return orthographicSize;
}

float Camera::getNearPlane() {
	return nearPlane;
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::mat4 Camera::getProjectionMatrix(float screenWidth, float screenHeight) {
	float aspectRatio = screenWidth / screenHeight;
	return orthographic ? ortho(orthographicSize, aspectRatio, nearPlane, farPlane) : perspective(fov, aspectRatio, nearPlane, farPlane);
}

glm::vec3 Camera::getTarget() {
	return target;
}

glm::mat4 Camera::getTranslationMatrix() {
	return glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-position.x, -position.y, -position.z, 1
	);
}

glm::mat4 Camera::getViewMatrix() {
	return lookAt(target, position, glm::vec3(0, 1, 0)) * getTranslationMatrix();
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
	float fovRad = glm::radians(fov);

	float c = tan(fovRad / 2);
	
	return glm::mat4(
		1 / (aspectRatio * c), 0, 0, 0,
		0, 1 / c, 0, 0,
		0, 0, -((farPlane + nearPlane) / (farPlane - nearPlane)), -1,
		0, 0, -((2 * farPlane * nearPlane) / (farPlane - nearPlane)), 1
	);
}

void Camera::setFarPlane(float farPlane) {
	this->farPlane = farPlane;
}

void Camera::setFov(float fov) {
	this->fov = fov;
}

void Camera::setNearPlane(float nearPlane) {
	this->nearPlane = nearPlane;
}

void Camera::setOrthographic(bool orthographic) {
	this->orthographic = orthographic;
}

void Camera::setOrthographicSize(float orthographicSize) {
	this->orthographicSize = orthographicSize;
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}

void Camera::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Camera::setTarget(glm::vec3 target) {
	this->target = target;
}

void Camera::setTarget(float x, float y, float z) {
	target = glm::vec3(x, y, z);
}