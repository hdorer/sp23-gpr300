#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "EW/Shader.h"
#include "EW/EwMath.h"
#include "EW/Camera.h"
#include "EW/Mesh.h"
#include "EW/Transform.h"
#include "EW/ShapeGen.h"

#include "HD/Lights.h"
#include "HD/Material.h"
#include <iostream>

void processInput(GLFWwindow* window);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

float lastFrameTime;
float deltaTime;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

double prevMouseX;
double prevMouseY;
bool firstMouseInput = false;

/* Button to lock / unlock mouse
* 1 = right, 2 = middle
* Mouse will start locked. Unlock it to use UI
* */
const int MOUSE_TOGGLE_BUTTON = 1;
const float MOUSE_SENSITIVITY = 0.1f;
const float CAMERA_MOVE_SPEED = 5.0f;
const float CAMERA_ZOOM_SPEED = 3.0f;

Camera camera((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);

glm::vec3 bgColor = glm::vec3(0);
glm::vec3 lightPosition = glm::vec3(0.0f, 3.0f, 0.0f);

bool wireFrame = false;

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lighting", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	//Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Setup UI Platform/Renderer backends
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//Dark UI theme.
	ImGui::StyleColorsDark();

	//Used to draw shapes. This is the shader you will be completing.
	Shader litShader("shaders/defaultLit.vert", "shaders/defaultLit.frag");

	//Used to draw light sphere
	Shader unlitShader("shaders/defaultLit.vert", "shaders/unlit.frag");

	ew::MeshData cubeMeshData;
	ew::createCube(1.0f, 1.0f, 1.0f, cubeMeshData);
	ew::MeshData sphereMeshData;
	ew::createSphere(0.5f, 64, sphereMeshData);
	ew::MeshData cylinderMeshData;
	ew::createCylinder(1.0f, 0.5f, 64, cylinderMeshData);
	ew::MeshData planeMeshData;
	ew::createPlane(1.0f, 1.0f, planeMeshData);

	ew::Mesh cubeMesh(&cubeMeshData);
	ew::Mesh sphereMesh(&sphereMeshData);
	ew::Mesh planeMesh(&planeMeshData);
	ew::Mesh cylinderMesh(&cylinderMeshData);

	//Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Initialize shape transforms
	ew::Transform cubeTransform;
	ew::Transform sphereTransform;
	ew::Transform planeTransform;
	ew::Transform cylinderTransform;
	
	//PointLight pLight;
	//SpotLight sLight;
	DirectionalLight dLight;
	
	Material material;

	cubeTransform.position = glm::vec3(-2.0f, 0.0f, 0.0f);
	sphereTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	planeTransform.position = glm::vec3(0.0f, -1.0f, 0.0f);
	planeTransform.scale = glm::vec3(10.0f);

	cylinderTransform.position = glm::vec3(2.0f, 0.0f, 0.0f);

	/*pLight.transform.scale = glm::vec3(0.5f);
	pLight.transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	pLight.transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	pLight.color = glm::vec3(0.8, 1.0, 0.8);
	pLight.intensity = 1.0;
	pLight.ambientLevel = 0.8;
	pLight.minRadius = 0.5;
	pLight.maxRadius = 8;*/

	/*sLight.transform.scale = glm::vec3(0.5f);
	sLight.transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	sLight.transform.rotation = glm::vec3(90.0f, 0.0f, 0.0f);
	sLight.color = glm::vec3(0.8, 1.0, 0.8);
	sLight.intensity = 1.0;
	sLight.ambientLevel = 0.8;
	sLight.minAngle = 1;
	sLight.maxAngle = 10;*/

	dLight.transform.scale = glm::vec3(0.5f);
	dLight.transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
	dLight.transform.rotation = glm::vec3(90.0f, 0.0f, 0.0f);
	dLight.color = glm::vec3(0.8, 1.0, 0.8);
	dLight.intensity = 1.0;
	dLight.ambientLevel = 0.8;
	dLight.name = "Directional Light";

	material.color = glm::vec3(1.0, 0.6, 0.8);
	material.ambientK = 0.5;
	material.diffuseK = 0.2;
	material.specularK = 0.8;
	material.shininess = 256;

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(bgColor.r,bgColor.g,bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		deltaTime = time - lastFrameTime;
		lastFrameTime = time;

		//Draw
		litShader.use();
		litShader.setMat4("_Projection", camera.getProjectionMatrix());
		litShader.setMat4("_View", camera.getViewMatrix());
		litShader.setVec3("cameraPosition", camera.getPosition());
		
		/*litShader.setVec3("pLight.position", pLight.transform.position);
		litShader.setVec3("pLight.color", pLight.color);
		litShader.setFloat("pLight.intensity", pLight.intensity);
		litShader.setFloat("pLight.ambientLevel", pLight.ambientLevel);
		litShader.setFloat("pLight.minRadius", pLight.minRadius);
		litShader.setFloat("pLight.maxRadius", pLight.maxRadius);*/

		/*litShader.setVec3("sLight.position", sLight.transform.position);
		litShader.setVec3("sLight.direction", sLight.direction());
		litShader.setVec3("sLight.color", sLight.color);
		litShader.setFloat("sLight.intensity", sLight.intensity);
		litShader.setFloat("sLight.ambientLevel", sLight.ambientLevel);
		litShader.setFloat("sLight.minAngle", sLight.minAngle);
		litShader.setFloat("sLight.maxAngle", sLight.maxAngle);*/

		litShader.setVec3("dLight.position", dLight.transform.position);
		litShader.setVec3("dLight.direction", dLight.direction());
		litShader.setVec3("dLight.color", dLight.color);
		litShader.setFloat("dLight.intensity", dLight.intensity);
		litShader.setFloat("dLight.ambientLevel", dLight.ambientLevel);

		litShader.setVec3("material.color", material.color);
		litShader.setFloat("material.ambientK", material.ambientK);
		litShader.setFloat("material.diffuseK", material.diffuseK);
		litShader.setFloat("material.specularK", material.specularK);
		litShader.setFloat("material.shininess", material.shininess);

		//Draw cube
		litShader.setMat4("_Model", cubeTransform.getModelMatrix());
		cubeMesh.draw();

		//Draw sphere
		litShader.setMat4("_Model", sphereTransform.getModelMatrix());
		sphereMesh.draw();

		//Draw cylinder
		litShader.setMat4("_Model", cylinderTransform.getModelMatrix());
		cylinderMesh.draw();

		//Draw plane
		litShader.setMat4("_Model", planeTransform.getModelMatrix());
		planeMesh.draw();

		//Draw light as a small sphere using unlit shader, ironically.
		unlitShader.use();
		unlitShader.setMat4("_Projection", camera.getProjectionMatrix());
		unlitShader.setMat4("_View", camera.getViewMatrix());
		/*unlitShader.setMat4("_Model", pLight.transform.getModelMatrix());
		unlitShader.setVec3("_Color", pLight.color);*/
		/*unlitShader.setMat4("_Model", sLight.transform.getModelMatrix());
		unlitShader.setVec3("_Color", sLight.color);*/
		unlitShader.setMat4("_Model", dLight.transform.getModelMatrix());
		unlitShader.setVec3("_Color", dLight.color);
		sphereMesh.draw();

		//Draw UI
		ImGui::Begin("Settings");

		/*ImGui::ColorEdit3("Light Color", &pLight.color.r);
		ImGui::DragFloat3("Light Position", &pLight.transform.position.x);
		ImGui::DragFloat3("Light Rotation", &pLight.transform.rotation.x);*/
		/*ImGui::ColorEdit3("Light Color", &sLight.color.x);
		ImGui::DragFloat3("Light Position", &sLight.transform.position.x);
		ImGui::DragFloat3("Light Rotation", &sLight.transform.rotation.x);*/
		dLight.drawGui();
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
//Author: Eric Winebrenner
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	camera.setAspectRatio((float)SCREEN_WIDTH / SCREEN_HEIGHT);
	glViewport(0, 0, width, height);
}
//Author: Eric Winebrenner
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//Reset camera
	if (keycode == GLFW_KEY_R && action == GLFW_PRESS) {
		camera.setPosition(glm::vec3(0, 0, 5));
		camera.setYaw(-90.0f);
		camera.setPitch(0.0f);
		firstMouseInput = false;
	}
	if (keycode == GLFW_KEY_1 && action == GLFW_PRESS) {
		wireFrame = !wireFrame;
		glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);
	}
}
//Author: Eric Winebrenner
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (abs(yoffset) > 0) {
		float fov = camera.getFov() - (float)yoffset * CAMERA_ZOOM_SPEED;
		camera.setFov(fov);
	}
}
//Author: Eric Winebrenner
void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
		return;
	}
	if (!firstMouseInput) {
		prevMouseX = xpos;
		prevMouseY = ypos;
		firstMouseInput = true;
	}
	float yaw = camera.getYaw() + (float)(xpos - prevMouseX) * MOUSE_SENSITIVITY;
	camera.setYaw(yaw);
	float pitch = camera.getPitch() - (float)(ypos - prevMouseY) * MOUSE_SENSITIVITY;
	pitch = glm::clamp(pitch, -89.9f, 89.9f);
	camera.setPitch(pitch);
	prevMouseX = xpos;
	prevMouseY = ypos;
}
//Author: Eric Winebrenner
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//Toggle cursor lock
	if (button == MOUSE_TOGGLE_BUTTON && action == GLFW_PRESS) {
		int inputMode = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
		glfwSetInputMode(window, GLFW_CURSOR, inputMode);
		glfwGetCursorPos(window, &prevMouseX, &prevMouseY);
	}
}

//Author: Eric Winebrenner
//Returns -1, 0, or 1 depending on keys held
float getAxis(GLFWwindow* window, int positiveKey, int negativeKey) {
	float axis = 0.0f;
	if (glfwGetKey(window, positiveKey)) {
		axis++;
	}
	if (glfwGetKey(window, negativeKey)) {
		axis--;
	}
	return axis;
}

//Author: Eric Winebrenner
//Get input every frame
void processInput(GLFWwindow* window) {

	float moveAmnt = CAMERA_MOVE_SPEED * deltaTime;

	//Get camera vectors
	glm::vec3 forward = camera.getForward();
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0,1,0)));
	glm::vec3 up = glm::normalize(glm::cross(forward, right));

	glm::vec3 position = camera.getPosition();
	position += forward * getAxis(window, GLFW_KEY_W, GLFW_KEY_S) * moveAmnt;
	position += right * getAxis(window, GLFW_KEY_D, GLFW_KEY_A) * moveAmnt;
	position += up * getAxis(window, GLFW_KEY_Q, GLFW_KEY_E) * moveAmnt;
	camera.setPosition(position);
}
