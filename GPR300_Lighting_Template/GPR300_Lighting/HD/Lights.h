#pragma once

#include "../EW/Transform.h"
#include "../imgui/imgui.h"
#include "glm/glm.hpp"
#include <string>

struct DirectionalLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
	std::string name;

	glm::vec3 direction() {
		float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		float y = sin(glm::radians(transform.rotation.x));
		float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

		return glm::normalize(glm::vec3(x, y, z));
	}

	void drawGui() {
		ImGui::ColorEdit3((name + " Color").c_str(), &color.x);
		ImGui::DragFloat3((name + " Position").c_str(), &transform.position.x);
		ImGui::DragFloat2((name + " Rotation").c_str(), &transform.rotation.x);
		ImGui::SliderFloat((name + " Intensity").c_str(), &intensity, 0.0, 1.0);
		ImGui::SliderFloat((name + " Ambient Level").c_str(), &ambientLevel, 0.0, 1.0);
	}
};

struct PointLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
	float minRadius;
	float maxRadius;
};

struct SpotLight {
	ew::Transform transform;
	glm::vec3 color;
	float intensity;
	float ambientLevel;
	float minAngle;
	float maxAngle;
	std::string name;

	glm::vec3 direction() {
		float x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
		float y = sin(glm::radians(transform.rotation.x));
		float z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

		return glm::normalize(glm::vec3(x, y, z));
	}

	void drawGui() {
		ImGui::ColorEdit3((name + " Color").c_str(), &color.x);
		ImGui::DragFloat3((name + " Position").c_str(), &transform.position.x);
		ImGui::DragFloat2((name + " Rotation").c_str(), &transform.rotation.x);
		ImGui::SliderFloat((name + " Intensity").c_str(), &intensity, 0.0, 1.0);
		ImGui::SliderFloat((name + " Ambient Level").c_str(), &ambientLevel, 0.0, 1.0);
		ImGui::DragFloat((name + " Min Angle").c_str(), &minAngle);
		ImGui::DragFloat((name + " Max Angle").c_str(), &maxAngle);
	}
};