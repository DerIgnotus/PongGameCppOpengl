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
#include "Ball.h"


bool checkCollision(float ballX, float ballY, float ballSize,
	float paddleX, float paddleY, float paddleWidth, float paddleHeight) {
	bool collisionX = ballX + ballSize >= paddleX && paddleX + paddleWidth >= ballX;
	bool collisionY = ballY + ballSize >= paddleY && paddleY + paddleHeight >= ballY;
	return collisionX && collisionY;
}


void resetBall(Ball& ball) {
	ball.x = 600; // Center X
	ball.y = 400; // Center Y
	ball.velocityX = (rand() % 2 == 0) ? -100.0f : 100.0f; // Random direction
	ball.velocityY = (rand() % 2 == 0) ? -100.0f : 100.0f;
	ball.additionalSpeed = 1.0f;
}

int main()
{
	int player_1_score = 0;
	int player_2_score = 0;

	// Initialize GLFW
	glfwInit();

	// Set GLFW hints like the OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::vector<Rectangle> rectangles;
	
	GLfloat vertices[] = {
			// Position    // Texture Coords
			-0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
			0.5f,  0.5f,  1.0f, 1.0f, // Top-right
			-0.5f,  0.5f,  0.0f, 1.0f  // Top-left
	};
	
	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Create the window
	// Check if window creating failed
	GLFWwindow* window = glfwCreateWindow(1200, 800, "Pong", NULL, NULL);
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
	glViewport(0, 0, 1200, 800);



	// Create Shaderprogram
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();

	// Correct View
	glm::mat4 projection = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1.0f, 1.0f);
	GLuint projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	Rectangle::VAO = vao.ID;

	Rectangle rect_1(100.0f, 400.0f, 25, 135);
	Rectangle rect_2(1200.0f - 100.0f, 400.0f, 25, 135);

	rectangles.push_back(rect_1);
	rectangles.push_back(rect_2);

	//Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture ballImage("circle_no_bg.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Ball::VAO = vao.ID;
	Ball ball(600.0f, 400.0f, 30.0f, 100.0f, 100.0f, ballImage.ID);


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear screen
		glClearColor(0.0f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use shader
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			rect_1.Move(0);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			rect_1.Move(1);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			rect_2.Move(0);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			rect_2.Move(1);
		}

		ball.Update(0.02f);

		if (checkCollision(ball.x, ball.y, ball.size, rect_1.posX, rect_1.posY, rect_1.width, rect_1.height)) 
		{
			ball.velocityX = -ball.velocityX;
			ball.additionalSpeed += 0.1f;
		}

		if (checkCollision(ball.x, ball.y, ball.size, rect_2.posX, rect_2.posY, rect_2.width, rect_2.height)) 
		{
			ball.velocityX = -ball.velocityX;
			ball.additionalSpeed += 0.1f;
		}

		if (ball.x - (ball.size / 2) <= 0) 
		{
			player_2_score++;
			std::cout << "Player 1: " << player_1_score << " Player 2: " << player_2_score << std::endl;
			resetBall(ball);
		}

		if (ball.x + (ball.size /2) >= 1200) 
		{
			player_1_score++;
			std::cout << "Player 1: " << player_1_score << " Player 2: " << player_2_score << std::endl;
			resetBall(ball);
		}

		if (ball.y - (ball.size / 2) <= 0 || ball.y + (ball.size / 2) >= 800) 
		{
			ball.velocityY = -ball.velocityY; // Reverse Y direction
			ball.additionalSpeed += 0.1f;
		}

		rect_1.Draw(shaderProgram);
		rect_2.Draw(shaderProgram);

		
		ball.Draw(shaderProgram);

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
unsigned int Ball::VAO = 0;