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
	enabled = true;
}

void DirectionalLight::drawGui() {
	if(ImGui::CollapsingHeader((name + " Settings").c_str())) {
		ImGui::Checkbox((name +" Enabled").c_str(), & enabled);
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

bool DirectionalLight::getEnabled() {
	return enabled;
}

glm::mat4 DirectionalLight::getModelMatrix() {
	return transform.getModelMatrix();
}

void DirectionalLight::setName(std::string name) {
	this->name = name;
}

void DirectionalLight::setShaderValues(Shader* shader) {
	shader->setVec3("dLight.position", transform.position);
	shader->setVec3("dLight.color", color);
	shader->setFloat("dLight.intensity", intensity);
	shader->setFloat("dLight.ambientLevel", ambientLevel);
}

void PointLight::drawGui() {
	if(ImGui::CollapsingHeader((name + " Settings").c_str())) {
		ImGui::Checkbox((name + " Enabled").c_str(), &enabled);
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

bool PointLight::getEnabled() {
	return enabled;
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
	enabled = true;
}

void PointLight::setName(std::string name) {
	this->name = name;
}

void PointLight::setShaderValues(Shader* shader) {
	shader->setVec3("pLights[0].position", transform.position);
	shader->setVec3("pLights[0].color", color);
	shader->setFloat("pLights[0].intensity", intensity);
	shader->setFloat("pLights[0].ambientLevel", ambientLevel);
	shader->setFloat("pLights[0].minRadius", minRadius);
	shader->setFloat("pLights[0].maxRadius", maxRadius);
}

void PointLight::setShaderValues(Shader* shader, int shaderIndex) {
	shader->setVec3("pLights[" + std::to_string(shaderIndex) + "].position", transform.position);
	shader->setVec3("pLights[" + std::to_string(shaderIndex) + "].color", color);
	shader->setFloat("pLights[" + std::to_string(shaderIndex) + "].intensity", intensity);
	shader->setFloat("pLights[" + std::to_string(shaderIndex) + "].ambientLevel", ambientLevel);
	shader->setFloat("pLights[" + std::to_string(shaderIndex) + "].minRadius", minRadius);
	shader->setFloat("pLights[" + std::to_string(shaderIndex) + "].maxRadius", maxRadius);
}

glm::vec3 SpotLight::direction() {
	float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	float y = sin(glm::radians(transform.rotation.x));
	float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

	return glm::normalize(glm::vec3(x, y, z));
}

void SpotLight::drawGui() {
	if(ImGui::CollapsingHeader((name + " Settings").c_str())) {
		ImGui::Checkbox((name + " Enabled").c_str(), &enabled);
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

bool SpotLight::getEnabled() {
	return enabled;
}

glm::mat4 SpotLight::getModelMatrix() {
	return transform.getModelMatrix();
}

void SpotLight::setName(std::string name) {
	this->name = name;
}

void SpotLight::setShaderValues(Shader* shader) {
	shader->setVec3("sLights[0].position", transform.position);
	shader->setVec3("sLights[0].direction", direction());
	shader->setVec3("sLights[0].color", color);
	shader->setFloat("sLights[0].intensity", intensity);
	shader->setFloat("sLights[0].ambientLevel", ambientLevel);
	shader->setFloat("sLights[0].minAngle", minAngle);
	shader->setFloat("sLights[0].maxAngle", maxAngle);
}

void SpotLight::setShaderValues(Shader* shader, int shaderIndex) {
	shader->setVec3("sLights[" + std::to_string(shaderIndex) + "].position", transform.position);
	shader->setVec3("sLights[" + std::to_string(shaderIndex) + "].direction", direction());
	shader->setVec3("sLights[" + std::to_string(shaderIndex) + "].color", color);
	shader->setFloat("sLights[" + std::to_string(shaderIndex) + "].intensity", intensity);
	shader->setFloat("sLights[" + std::to_string(shaderIndex) + "].ambientLevel", ambientLevel);
	shader->setFloat("sLights[" + std::to_string(shaderIndex) + "].minAngle", minAngle);
	shader->setFloat("sLights[" + std::to_string(shaderIndex) + "].maxAngle", maxAngle);
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
	enabled = true;
}