#include "Transform.h"

glm::mat4 Transform::getModelMatrix() {
	return glm::mat4(1) * getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
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

Transform::Transform() {
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
}