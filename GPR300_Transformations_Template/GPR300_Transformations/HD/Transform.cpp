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
	glm::mat4 xRotation = glm::mat4(
		1, 0, 0, 0,
		0, cos(rotation.x), sin(rotation.x), 0,
		0, -sin(rotation.x), cos(rotation.x), 0,
		0, 0, 0, 1
	);

	glm::mat4 yRotation = glm::mat4(
		cos(rotation.y), 0, -sin(rotation.y), 0,
		0, 1, 0, 0,
		sin(rotation.y), 0, cos(rotation.y), 0,
		0, 0, 0, 1
	);

	glm::mat4 zRotation = glm::mat4(
		cos(rotation.z), sin(rotation.z), 0, 0,
		-sin(rotation.z), cos(rotation.z), 0, 0,
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