#include "Lights.h"

glm::vec3 DirectionalLight::direction() {
	float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	float y = sin(glm::radians(transform.rotation.x));
	float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

	return glm::normalize(glm::vec3(x, y, z));
}

DirectionalLight::DirectionalLight() {
	transform.scale = glm::vec3(0.5f);
	transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	transform.rotation = glm::vec3(90.0f, 0.0f, 0.0f);
	color = glm::vec3(0.8, 1.0, 0.8);
	intensity = 1.0;
	ambientLevel = 0.8;
	name = "Directional Light";
}

DirectionalLight::DirectionalLight(std::string name) {
	transform.scale = glm::vec3(0.5f);
	transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	transform.rotation = glm::vec3(90.0f, 0.0f, 0.0f);
	color = glm::vec3(0.8, 1.0, 0.8);
	intensity = 1.0;
	ambientLevel = 0.8;
	this->name = name;
}

void DirectionalLight::drawGui() {
	if(ImGui::CollapsingHeader((name + " Settings").c_str())) {
		ImGui::ColorEdit3((name + " Color").c_str(), &color.x);
		ImGui::DragFloat3((name + " Position").c_str(), &transform.position.x, 0.1);
		ImGui::DragFloat2((name + " Rotation").c_str(), &transform.rotation.x, 0.1);
		ImGui::SliderFloat((name + " Intensity").c_str(), &intensity, 0.0, 1.0);
		ImGui::SliderFloat((name + " Ambient Level").c_str(), &ambientLevel, 0.0, 1.0);
	}
}

glm::vec3 DirectionalLight::getColor() {
	return color;
}

glm::mat4 DirectionalLight::getModelMatrix() {
	return transform.getModelMatrix();
}

void DirectionalLight::setShaderValues(Shader* shader) {
	shader->setVec3("pLight.position", transform.position);
	shader->setVec3("pLight.color", color);
	shader->setFloat("pLight.intensity", intensity);
	shader->setFloat("pLight.ambientLevel", ambientLevel);
}

void PointLight::drawGui() {
	if(ImGui::CollapsingHeader((name + " Settings").c_str())) {
		ImGui::ColorEdit3((name + " Color").c_str(), &color.x);
		ImGui::DragFloat3((name + " Position").c_str(), &transform.position.x, 0.1);
		ImGui::DragFloat2((name + " Rotation").c_str(), &transform.rotation.x, 0.1);
		ImGui::SliderFloat((name + " Intensity").c_str(), &intensity, 0.0, 1.0);
		ImGui::SliderFloat((name + " Ambient Level").c_str(), &ambientLevel, 0.0, 1.0);
		ImGui::DragFloat((name + " Min Radius").c_str(), &minRadius, 0.1);
		ImGui::DragFloat((name + "Max radius").c_str(), &maxRadius, 0.1);
	}
}

glm::vec3 PointLight::getColor() {
	return color;
}

glm::mat4 PointLight::getModelMatrix() {
	return transform.getModelMatrix();
}

PointLight::PointLight() {
	transform.scale = glm::vec3(0.5f);
	transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.8, 1.0, 0.8);
	intensity = 1.0;
	ambientLevel = 0.8;
	minRadius = 0.5;
	maxRadius = 8;
	name = "Point Light";
}

PointLight::PointLight(std::string name) {
	transform.scale = glm::vec3(0.5f);
	transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.8, 1.0, 0.8);
	intensity = 1.0;
	ambientLevel = 0.8;
	minRadius = 0.5;
	maxRadius = 8;
	this->name = name;
}

void PointLight::setShaderValues(Shader* shader) {
	shader->setVec3("pLight.position", transform.position);
	shader->setVec3("pLight.color", color);
	shader->setFloat("pLight.intensity", intensity);
	shader->setFloat("pLight.ambientLevel", ambientLevel);
	shader->setFloat("pLight.minRadius", minRadius);
	shader->setFloat("pLight.maxRadius", maxRadius);
}

glm::vec3 SpotLight::direction() {
	float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	float y = sin(glm::radians(transform.rotation.x));
	float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

	return glm::normalize(glm::vec3(x, y, z));
}

void SpotLight::drawGui() {
	if(ImGui::CollapsingHeader((name + " Settings").c_str())) {
		ImGui::ColorEdit3((name + " Color").c_str(), &color.x);
		ImGui::DragFloat3((name + " Position").c_str(), &transform.position.x, 0.1);
		ImGui::DragFloat2((name + " Rotation").c_str(), &transform.rotation.x, 0.1);
		ImGui::SliderFloat((name + " Intensity").c_str(), &intensity, 0.0, 1.0);
		ImGui::SliderFloat((name + " Ambient Level").c_str(), &ambientLevel, 0.0, 1.0);
		ImGui::DragFloat((name + " Min Angle").c_str(), &minAngle, 0.1);
		ImGui::DragFloat((name + " Max Angle").c_str(), &maxAngle, 0.1);
	}
}

glm::vec3 SpotLight::getColor() {
	return color;
}

glm::mat4 SpotLight::getModelMatrix() {
	return transform.getModelMatrix();
}

void SpotLight::setShaderValues(Shader* shader) {
	shader->setVec3("sLight.position", transform.position);
	shader->setVec3("sLight.direction", direction());
	shader->setVec3("sLight.color", color);
	shader->setFloat("sLight.intensity", intensity);
	shader->setFloat("sLight.ambientLevel", ambientLevel);
	shader->setFloat("sLight.minAngle", minAngle);
	shader->setFloat("sLight.maxAngle", maxAngle);
}

SpotLight::SpotLight() {
	transform.scale = glm::vec3(0.5f);
	transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	transform.rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
	color = glm::vec3(0.8, 1.0, 0.8);
	intensity = 1.0;
	ambientLevel = 0.8;
	minAngle = 1;
	maxAngle = 10;
	name = "Spot Light";
}

SpotLight::SpotLight(std::string name) {
	transform.scale = glm::vec3(0.5f);
	transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	transform.rotation = glm::vec3(-90.0f, 0.0f, 0.0f);
	color = glm::vec3(0.8, 1.0, 0.8);
	intensity = 1.0;
	ambientLevel = 0.8;
	minAngle = 1;
	maxAngle = 10;
	this->name = name;
}