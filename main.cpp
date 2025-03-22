#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Rectangle.h"


int main()
{
	// Initialize GLFW
	glfwInit();

	// Set GLFW hints like the OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::vector<Rectangle> rectangles;
	
	GLfloat vertices[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f,  0.5f,
			-0.5f,  0.5f,
	};
	
	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Create the window
	// Check if window creating failed
	GLFWwindow* window = glfwCreateWindow(800, 800, "Cpp Game", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}

	// Make window our context
	glfwMakeContextCurrent(window);

	// Load	GLAD
	gladLoadGL();

	// Set the viewport
	glViewport(0, 0, 800, 800);

	// Create Shaderprogram
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();

	// Correct View
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
	GLuint projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	Rectangle::VAO = vao.ID;

	Rectangle rect_1(100.0f, 100.0f, 100, 100);
	Rectangle rect_2(200.0f, 200.0f, 100, 100);

	rectangles.push_back(rect_1);
	rectangles.push_back(rect_2);


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear screen
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use shader
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);


		rect_1.Draw(shaderProgram);
		rect_2.Draw(shaderProgram);

		// Swap buffers
		glfwSwapBuffers(window);


		// Handle Events
		glfwPollEvents();
	}

	// Clean things up

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

unsigned int Rectangle::VAO = 0;