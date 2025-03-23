#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderClass.h"

class Ball 
{
public:
    float x, y, size, velocityX, velocityY;
    float additionalSpeed = 1.0f;
    static unsigned int VAO;
    unsigned int texture;

    Ball(float startX, float startY, float s, float vX, float vY, unsigned int tex)
        : x(startX), y(startY), size(s), velocityX(vX), velocityY(vY), texture(tex) {
    }

    void Update(float deltaTime);
    void Draw(Shader& shader);
};

