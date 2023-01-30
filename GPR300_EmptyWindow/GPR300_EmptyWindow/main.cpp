#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

//void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);

//TODO: Vertex shader source code
const char* vertexShaderSource =
"#version 450											\n"
"layout (location = 0) in vec3 vPos;					\n"
"layout (location = 1) in vec3 vColor;					\n"
"layout (location = 2) in float direction;				\n"
"out vec3 Color;										\n"
"uniform float iTime;									\n"
"void main() {											\n"
"	Color = vColor;										\n"
"	float yValue = vPos.y + (sin(iTime) / 4);			\n"
"	gl_Position = vec4(vPos.x, yValue, vPos.z, 1.0);	\n"
"}														\0";

//TODO: Fragment shader source code
const char* fragmentShaderSource =
"#version 450											\n"
"out vec4 FragColor;									\n"
"in vec3 Color;											\n"
"uniform float iTime;									\n"
"void main() {											\n"
"	FragColor = vec4(abs(sin(iTime)) * Color, 1.0);		\n"
"}														\0";

struct Vec3 {
	float x, y, z;
};

struct Color {
	float r, g, b, a;
};

struct Vertex {
	Vec3 position;
	Color color;
};

//TODO: Vertex data array
const Vertex vertexData[] = {
	// triangle 1
	Vertex{ Vec3{ -0.5, 0.5, 0.0 }, Color{ 1.0, 0.0, 0.0, 1.0 } },
	Vertex{ Vec3{ -0.5, -0.5, 0.0 }, Color{ 0.0, 1.0, 0.0, 1.0 } },
	Vertex{ Vec3{ 0.0, 0.0, 0.0 }, Color{ 0.0, 0.0, 1.0, 1.0 } },
	// triangle 2
	Vertex{ Vec3{ 0.5, 0.5, 0.0 }, Color{ 1.0, 0.0, 0.0, 1.0 } },
	Vertex{ Vec3{ 0.0, 0.0, 0.0 }, Color{ 0.0, 1.0, 0.0, 1.0 } },
	Vertex{ Vec3{ 0.5, -0.5, 0.0 }, Color{ 0.0, 0.0, 1.0, 1.0 } }
};

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGLExample", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);

	//TODO: Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//TODO: Get vertex shader compilation status and output info log
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Failed to compile vertex shader: %s", infoLog);
	}
	
	//TODO: Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//TODO: Get fragment shader compilation status and output info log
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Failed to compile vertex shader: %s", infoLog);
	}

	//TODO: Create shader program
	GLuint shaderProgram = glCreateProgram();

	//TODO: Attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//TODO: Link shader program
	glLinkProgram(shaderProgram);

	//TODO: Check for link status and output errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Failed to link shader program: %s", infoLog);
	}

	//TODO: Delete vertex + fragment shader objects
	//glDeleteShader(...)

	//TODO: Create and bind Vertex Array Object (VAO)
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//TODO: Create and bind Vertex Buffer Object (VBO), fill with vertexData
	GLuint vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//TODO: Define vertex attribute layout (position (xyz))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(0);

	// Define vertex attribute layout (color (rgba))
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO:Use shader program
		glUseProgram(shaderProgram);

		// Set uniforms
		float time = (float)glfwGetTime();
		glUniform1f(glGetUniformLocation(shaderProgram, "iTime"), time);
		
		//TODO: Draw triangle (6 indices!)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

