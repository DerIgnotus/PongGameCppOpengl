#include <glad/glad.h>
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Rectangle
{
public:
	Rectangle(float pos_x, float pos_y, int width, int height);
	~Rectangle();
	void Move(int direction);
	void BindVAO();
	float posX, posY;
private:
	
	std::vector<GLfloat> vertices;
	VAO vao;
	VBO vbo;
	EBO ebo;
};
