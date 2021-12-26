#include <stdio.h>
#include<string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window Dimensions
const GLint WIDTH = 800, HEIGHT = 600;	

GLuint VBO;

// Vertex Shader
const char* vertexShaderSource = "						\n\
#version 330 core										\n\
layout(location = 0) in vec3 pos;						\n\
														\n\
void main() {											\n\
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);		\n\
}";

// Fragment Shader
const char* fragmentShaderSource = "					\n\
#version 330 core										\n\
out vec4 color;											\n\
														\n\
void main() {											\n\
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);				\n\
}";

const char* fragmentShaderSource2 = "					\n\
#version 330 core										\n\
out vec4 color;											\n\
														\n\
void main() {											\n\
	color = vec4(1.0f, 1.0f, 0.0f, 1.0f);				\n\
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
		glfwDestroyWindow;
		glfwTerminate;

		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Shader Code goes here
	GLuint vertexShader, fragmentShader, fragmentShader2;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	GLuint shaderProgram, shaderProgram2;
	shaderProgram = glCreateProgram();
	shaderProgram2 = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(fragmentShader);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader2);

	/*
	GLfloat verticies[] = {
		// First Triangle
		 0.5f,  0.5f, 0.0f,  
		 0.5f, -0.5f, 0.0f,  
		-0.5f,  0.5f, 0.0f,
		// Second Triangle
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	*/
	/*
	GLfloat verticies[] = {
		 0.5f,  0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f  
	};
	GLuint indicies[] = {
		0, 1, 3,
		1, 2, 3
	};
	*/
	GLfloat verticies[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	GLfloat verticies2[] = {
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	GLuint VAO, VAO2, VBO, VBO2, EBO;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbinds the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbinds the VAO
	glBindVertexArray(0);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies2), verticies2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Where our code is actually added

		glfwSwapBuffers(mainWindow);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}