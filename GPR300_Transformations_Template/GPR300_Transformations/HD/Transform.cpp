#include "Transform.h"

glm::mat4 Transform::getModelMatrix() {
	return glm::mat4(1) * getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

glm::vec3 Transform::getPosition() {
	return position;
}


glm::vec3 Transform::getRotation() {
	return rotation;
}

glm::mat4 Transform::getRotationMatrix() {
	float xRad = glm::radians(rotation.x);
	float yRad = glm::radians(rotation.y);
	float zRad = glm::radians(rotation.z);

	glm::mat4 xRotation = glm::mat4(
		1, 0, 0, 0,
		0, cos(xRad), sin(xRad), 0,
		0, -sin(xRad), cos(xRad), 0,
		0, 0, 0, 1
	);

	glm::mat4 yRotation = glm::mat4(
		cos(yRad), 0, -sin(yRad), 0,
		0, 1, 0, 0,
		sin(yRad), 0, cos(yRad), 0,
		0, 0, 0, 1
	);

	glm::mat4 zRotation = glm::mat4(
		cos(zRad), sin(zRad), 0, 0,
		-sin(zRad), cos(zRad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	return xRotation * yRotation * zRotation;
}

glm::vec3 Transform::getScale() {
	return scale;
}

glm::mat4 Transform::getScaleMatrix() {
	return glm::mat4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	);
}

glm::mat4 Transform::getTranslationMatrix() {
	return glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		position.x, position.y, position.z, 1
	);
}

void Transform::setPosition(glm::vec3 position) {
	this->position = position;
}

void Transform::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Transform::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
}

void Transform::setRotation(float x, float y, float z) {
	rotation = glm::vec3(x, y, z);
}

void Transform::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Transform::setScale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}

void Transform::setScale(float scaleFactor) {
	scale = glm::vec3(scaleFactor);
}

Transform::Transform() {
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
}