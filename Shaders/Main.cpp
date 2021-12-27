#include <stdio.h>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window Dimensions
const GLint WIDTH = 800, HEIGHT = 600;	


// Vertex Shader
const char* vertexShaderSource = "						\n\
#version 330 core										\n\
layout(location = 0) in vec3 pos;						\n\
layout(location = 1) in vec3 color;						\n\
														\n\
out vec3 ourColor;										\n\
														\n\
void main() {											\n\
	gl_Position = vec4(pos, 1.0f);						\n\
	ourColor = color;									\n\
}";

// Fragment Shader
const char* fragmentShaderSource = "					\n\
#version 330 core										\n\
out vec4 fragColor;										\n\
in vec3 ourColor;										\n\
														\n\
														\n\
void main() {											\n\
	fragColor = vec4(ourColor, 1.0f);					\n\
}";


int main() {

	// Initilize GLFW
	if (!glfwInit()) {
		printf("GLFW initilization failed");
		glfwTerminate();

		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile ensures that there is no backwards compatability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allows for forward compatability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Creates Window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed");
		glfwTerminate();

		return 1;
	}

	// Get Buffer size information (Size of OpenGL viewport)
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extenstion features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW initilization failed");
		// Since window has now been created we must destroy it
		glfwDestroyWindow(mainWindow);
		glfwTerminate();

		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Shader Code goes here
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float verticies[] = {
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top   
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	// Vertex Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbinds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbinds the VAO
	glBindVertexArray(0);

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow)) {
		// Get + Handle user input events
		glfwPollEvents();

		// Clear Window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Where our code is actually added
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Where our code is actually added

		glfwSwapBuffers(mainWindow);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}