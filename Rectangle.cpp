#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(float pos_x, float pos_y, int w, int h) : posX(pos_x), posY(pos_y), width(w), height(h)
{

}

Rectangle::~Rectangle()
{

}

void Rectangle::Move(int direction)
{
	if (direction == 1)
	{
		posY -= 4.5f;
	}
	else
	{
		posY += 4.5f;
	}

	if (posY - (height / 2) < 0) 
	{
		posY = 0 + (height / 2);
	}

	if (posY + (height / 2) > 800) 
	{
		posY = 800 - (height / 2);
	}
}


void Rectangle::Draw(Shader &shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, 0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));
	shader.setMat4("model", model);

	shader.setBool("useTexture", false);
	shader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
