#pragma once

#include "../EW/Transform.h"
#include "../EW/Shader.h"
#include "../imgui/imgui.h"
#include "glm/glm.hpp"
#include <string>

class DirectionalLight {
	public:
		DirectionalLight();
		DirectionalLight(std::string name);

		glm::mat4 getModelMatrix();
		glm::vec3 getColor();

		glm::vec3 direction();
		void drawGui();
		void setShaderValues(Shader* shader);
	private:
		ew::Transform transform;
		glm::vec3 color;
		float intensity;
		float ambientLevel;
	
		std::string name = "Directional Light";
		bool enabled;
};

class PointLight {
	public:
		PointLight();
		PointLight(std::string name);

		glm::mat4 getModelMatrix();
		glm::vec3 getColor();
		
		void drawGui();
		void setShaderValues(Shader* shader);
	private:
		ew::Transform transform;
		glm::vec3 color;
		float intensity;
		float ambientLevel;
		float minRadius;
		float maxRadius;
	
		std::string name = "Point Light";
		bool enabled;
};

class SpotLight {
	public:
		SpotLight();
		SpotLight(std::string name);

		glm::mat4 getModelMatrix();
		glm::vec3 getColor();

		glm::vec3 direction();
		void drawGui();
		void setShaderValues(Shader* shader);
	private:
		ew::Transform transform;
		glm::vec3 color;
		float intensity;
		float ambientLevel;
		float minAngle;
		float maxAngle;

		std::string name = "Spot Light";
		bool enabled = true;
};