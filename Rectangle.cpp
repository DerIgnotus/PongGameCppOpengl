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
}


void Rectangle::Draw(Shader &shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, 0.0f));
	model = glm::scale(model, glm::vec3(width, height, 1.0f));
	shader.setMat4("model", model);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
