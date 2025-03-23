#include "Ball.h"

void Ball::Update(float deltaTime)
{
	x += velocityX * deltaTime * additionalSpeed;
	y += velocityY * deltaTime * additionalSpeed;
}

void Ball::Draw(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(size, size, 1.0f));

    shader.setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.setInt("ballTexture", 0); // Only set for ball

	shader.setBool("useTexture", true);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
