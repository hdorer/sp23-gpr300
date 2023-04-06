#pragma once

#include "../EW/Transform.h"
#include "../EW/Shader.h"
#include "../imgui/imgui.h"
#include "glm/glm.hpp"
#include <string>

class DirectionalLight {
	public:
		DirectionalLight();

		glm::mat4 getModelMatrix();
		glm::vec3 getColor();
		bool getEnabled();

		void setName(std::string name);

		glm::vec3 direction();
		void drawGui();
		void setShaderValues(Shader* shader);
	private:
		ew::Transform transform;
		glm::vec3 color;
		float intensity;
		float ambientLevel;

		std::string name;
		bool enabled;
};

class PointLight {
	public:
		PointLight();

		glm::mat4 getModelMatrix();
		glm::vec3 getColor();
		bool getEnabled();

		void setName(std::string name);

		void drawGui();
		void setShaderValues(Shader* shader);
		void setShaderValues(Shader* shader, int shaderIndex);
	private:
		ew::Transform transform;
		glm::vec3 color;
		float intensity;
		float ambientLevel;
		float minRadius;
		float maxRadius;

		std::string name;
		bool enabled;
};