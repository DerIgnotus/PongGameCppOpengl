#include <glad/glad.h>
#include <vector>
#include "VAO.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderClass.h"

class Rectangle
{
public:
	float posX, posY;
	float width, height;
	static unsigned int VAO;

	Rectangle(float pos_x, float pos_y, int w, int h);
	~Rectangle();
	void Move(int direction);
	void Draw(Shader &shader);
};

